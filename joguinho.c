#include "raylib.h"
#include <stdlib.h>
#include <time.h>

void Gera_numero_de_caixas(int dificuldade, int *caixas);
int Desenha_caixas(int *caixas);
int Palpite_do_usuario();

int main(void){
    
    int largura=1200, altura=650;
    InitWindow(largura, altura, "Caixas");
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
    
    SetTargetFPS(60);
    srand(time(NULL));
    
    int caixas[100], rodada=0, dificuldade=1, quantidade_de_caixas, palpite;
    float tempo_inicial, tempo_atual;
    
    while(!WindowShouldClose()){
        rodada++;
        Gera_numero_de_caixas(dificuldade, caixas);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        quantidade_de_caixas=Desenha_caixas(caixas);
        DrawGrid(10, 1.0f);
        EndMode3D();
        
        DrawFPS(10, 10);
        EndDrawing();
        
        WaitTime(1.5);

        palpite=Palpite_do_usuario();
        

    }    
CloseWindow();   
}


void Gera_numero_de_caixas(int dificuldade, int *caixas){
    caixas[(rand() %50)]=1;
    for(int a=0;a<100;a++){
        if(((rand() %(100-dificuldade)))==0){
        caixas[a]=1;
        }
    }       
}

int Desenha_caixas(int *caixas){
    int contador_de_caixas=0, contador_de_linha=0;
    float x=-5.5, z=-4.5;
    Vector3 cubePosition = { 0.0f, 0.5f, 0.0f };
    for(int a=0;a<100;a++){
        x=x+1.0;
        if(a!=0 && a%10==0){
            x=-4.5;
            z=z+1.0;
            contador_de_linha++;
            }
            if(caixas[a]==1){
                if( (rand() %3)==0 && (a%(9+(10*contador_de_linha)))!=0 && (a-90)<0 && caixas[a+1] == 0 && caixas[a+10]==0 && caixas[a+11]==0){
                    contador_de_caixas++;
                    cubePosition.z = z+0.5;
                    cubePosition.x = x+0.5;
                    DrawCube(cubePosition, 2.0f, 1.0f, 2.0f, WHITE);
                    DrawCubeWires(cubePosition, 2.0f, 1.1f, 2.0f, BLACK);
                    caixas[a]=2;
                    caixas[a+1]=2;
                    caixas[a+10]=2;
                    caixas[a+11]=2;
                }
                else{
                    contador_de_caixas++;
                    cubePosition.z = z;
                    cubePosition.x = x;
                    DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, WHITE);
                    DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
                }
                
            }
            else{caixas[a]=0;}
        }
    return contador_de_caixas;
}

int Palpite_do_usuario(){
    int palpite=0;
    float tempo_inicial, tempo_atual;
    tempo_inicial=GetTime();
    tempo_atual=GetTime();
    while((tempo_atual-tempo_inicial)<3.5 && !WindowShouldClose()){
        tempo_atual=GetTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Palpite: %03i", palpite), 10, 40, 20, BLACK);
        if (IsKeyPressed(KEY_UP)) palpite++;
        if (IsKeyPressed(KEY_DOWN) && palpite!=0) palpite--;
        EndDrawing(); 
    }
return palpite;
}










