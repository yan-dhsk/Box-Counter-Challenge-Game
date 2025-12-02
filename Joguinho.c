#include "raylib.h"
#include <stdlib.h>
#include <time.h>


void Gera_numero_de_caixas(int dificuldade, int *caixas);
int Desenha_caixas(int *caixas);


int main(void){

    int screenWidth = 1200;
    int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "Caixas");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;
    
    
    DisableCursor();
    SetTargetFPS(60);
    int caixas[100], dificuldade=1, quantidade_de_caixas;
    char teste;
    srand(time(NULL));
    
    while(!WindowShouldClose()){
            BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            Gera_numero_de_caixas(dificuldade, caixas);
            quantidade_de_caixas=Desenha_caixas(caixas);
            DrawGrid(10, 1.0f);
                
            EndMode3D();
            teste = quantidade_de_caixas+48;
            DrawText("Quantidade de caixas:", 10, 40, 20, DARKGRAY);
            DrawText(&teste, 230, 40, 20, DARKGRAY);
            DrawFPS(10, 10);
            
        EndDrawing();
WaitTime(1.2);
dificuldade++;
    
    }
    
    CloseWindow();        



}

void Gera_numero_de_caixas(int dificuldade, int *caixas){
    caixas[rand() %50]=1;
    caixas[(rand() %99)+1]=1;
    for(int a=0;a<100;a++){
        if(((rand() %(100-dificuldade)))==0){
        caixas[a]=1;
        }
    }
}

int Desenha_caixas(int *caixas){
    int contador_de_caixas=0;
    float x=-5.5, z=-4.5;
    Vector3 cubePosition = { 0.0f, 0.5f, 0.0f };
    for(int a=0;a<100;a++){
        x=x+1.0;
        if(a!=0 && a%10==0){
                x=-4.5;
                z=z+1.0;
            }
        if(caixas[a]==1){
            contador_de_caixas++;
            cubePosition.z = z;
            cubePosition.x = x;
            DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, RED);
            DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
            }
        caixas[a]=0;
        }
    return contador_de_caixas;
    
    
    
}