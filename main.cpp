//
// Created by mwiner on 12/28/24.
//

#include "raylib.h"
#include <cmath>
#include <vector>
int main() {
    InitAudioDevice();
    const int screenW = 800;
    const int screenH = 400;
    InitWindow(screenW,screenH,"LANC++");
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("LANC++",10,10,20,RAYWHITE);
            DrawText("LANC Controller For Camera",10,30,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}