#include "wavegenerator.h"
#include <cmath>
#include <cstring>
Wave waveGenerator::waveGenerator(bool bit,float bitDuration,int sampleRate) {
    int sampleCount = static_cast<int>(sampleRate*bitDuration);
    if (bit) {
        for (int i = 0; i < sampleCount; i++) {
            float t = static_cast<float>(i) / sampleRate; // Time in seconds
            samples[i] = sinf(2.0f * PI * 1000 * t);      // Sine wave
        }
    } else {
        std::fill(samples.begin(),samples.end(),0.0f);
    }

    Wave wave = {0};
    wave.frameCount = sampleCount;
    wave.sampleRate = sampleRate;
    wave.sampleSize = 32;
    wave.channels = 1;

    wave.data = malloc(sampleCount * sizeof(float));
    std::memcpy(wave.data,samples.data(),sampleCount * sizeof(float));
    return wave;
}
Wave waveGenerator::generateCommand(const std::vector<uint8_t> &commandBytes, int baudRate, int sampleRate){
    float bitDuration = 1.0f / baudRate;
    std::vector<Wave> bitWaves;

    for (uint8_t byte : commandBytes){
        for (int i = 0;i < 8; i++){
            bool bit = (byte >> i) & 0x01;
            bitWaves.push_back(generateBit(bit,bitDuration,sampleRate));
        }
    }

    int totalSamples = 0;
    for (const Wave& bitWave : bitWaves) {
        totalSamples += bitWave.frameCount;
    }

    std::vector<float> combinedSamples(totalSamples);
    int offset = 0;
    for (const Wave& bitWave : bitWaves){
        std::memcpy(combinedSamples.data()+offset,bitWave.data,bitWave.frameCount*sizeof(float));
        offset+=bitWave.frameCount;
        UnloadWave(bitWave);
    }
    Wave commandWave = {0};
    commandWave.frameCount = totalSamples;
    commandWave.sampleRate = sampleRate;
    commandWave.sampleSize = 32;
    commandWave.channels = 1;

    commandWave.data = malloc(totalSamples*sizeof(float));
    std::memcpy(commandWave.data,combinedSamples.data(),totalSamples*sizeof(float));
    return commandWave;
}


















