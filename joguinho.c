#include "raylib.h"
#include <stdlib.h>
#include <time.h>

void Gera_numero_de_caixas(int dificuldade, int *caixas);
int Desenha_caixas(int *caixas);
int Palpite_do_usuario(Sound *toque, Font *fonte, int dificuldade);
void Revela_cubos(int contador, int *caixas);
int Checa_palpite(int palpite, int *vidas, int quantidade_de_caixas, Sound *derrota, Sound *palmas, Sound *boo, Sound *vitoria);
int Checa_vida(int *vidas);
void Desenha_status(int *vidas, int rodada, int pontos, Texture2D *vida_cheia, Texture2D *vida_vazia, Font *fonte);
void Mostra_cubos(Camera3D *camera, int *caixas);

int main(void){
    
    int largura=1200, altura=650;
    InitWindow(largura, altura, "Caixas");
    InitAudioDevice();
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
    
    SetTargetFPS(60);
    srand(time(NULL));
    
    int caixas[100], rodada=0, dificuldade=0, quantidade_de_caixas, palpite, vidas[]={1,1,1,1,1}, pontos=0, game_over=0;
    float tempo_atual, tempo_inicial;
    
    Texture2D vida_cheia=LoadTexture("assets/vida_cheia.png");
    Texture2D vida_vazia=LoadTexture("assets/vida_vazia.png");
    
    Font fonte=LoadFontEx("assets/tahoma.ttf", 120, 0, 0);
    
    Sound musica_de_fundo=LoadSound("sounds/Kevin MacLeod_ Blip Stream.mp3");
    Sound tambor=LoadSound("sounds/drum-roll-for-victory-366448.mp3");
    Sound derrota=LoadSound("sounds/derrota.mp3");
    Sound palmas=LoadSound("sounds/palmas.mp3");
    Sound booo=LoadSound("sounds/booo.mp3");
    Sound vitoria=LoadSound("sounds/vitoria.mp3");    
    Sound toque=LoadSound("sounds/toque.mp3");
    

    PlaySound(musica_de_fundo);
    while(!WindowShouldClose()){
        rodada++;
        for(int x=0;x<100;x++){caixas[x]=0;} 
        if(dificuldade<95){
            dificuldade=35+(rodada*2);
        }
        SetSoundVolume(musica_de_fundo, 0.3);
        ResumeSound(musica_de_fundo);
        
        if(!IsSoundPlaying(musica_de_fundo)){
            PlaySound(musica_de_fundo);
            SetSoundVolume(musica_de_fundo, 0.3);
        }
        
        Gera_numero_de_caixas(dificuldade, caixas);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Desenha_status(vidas, rodada, pontos, &vida_cheia, &vida_vazia, &fonte);
        
        BeginMode3D(camera);
        
        quantidade_de_caixas=Desenha_caixas(caixas);
        DrawGrid(10, 1.0f);
        
        EndMode3D();
        EndDrawing();
        
        tempo_inicial=GetTime();
        tempo_atual=GetTime();
        while((tempo_atual-tempo_inicial)<(2.4-(0.016*dificuldade)) && !WindowShouldClose()){
            tempo_atual=GetTime();
        }
        
        palpite=Palpite_do_usuario(&toque, &fonte, dificuldade);
        PauseSound(musica_de_fundo);
        
        SetSoundVolume(tambor, 1.2);
        PlaySound(tambor);
        Mostra_cubos(&camera, caixas);
        StopSound(tambor);
        
        if(!WindowShouldClose()){
            pontos+=Checa_palpite(palpite, vidas, quantidade_de_caixas, &derrota, &palmas, &booo, &vitoria);
            BeginDrawing();
            Desenha_status(vidas, rodada, pontos, &vida_cheia, &vida_vazia, &fonte);
            EndDrawing();
        }
        
        tempo_inicial=GetTime();
        tempo_atual=GetTime();
        while((tempo_atual-tempo_inicial)<2.0 && !WindowShouldClose()){
            tempo_atual=GetTime();
        }
        StopSound(booo);
        StopSound(derrota);
        StopSound(palmas);
        StopSound(vitoria);
        
        game_over=Checa_vida(vidas);
        if(game_over!=0){break;}

    }
StopSound(musica_de_fundo);  
UnloadSound(toque);
UnloadSound(palmas);
UnloadSound(vitoria);
UnloadSound(derrota);
UnloadSound(booo);
UnloadSound(tambor);
UnloadSound(musica_de_fundo);  
UnloadTexture(vida_cheia);
UnloadTexture(vida_vazia);
UnloadFont(fonte);
CloseWindow();
CloseAudioDevice();   
}


void Gera_numero_de_caixas(int dificuldade, int *caixas){
    caixas[(rand() %50)]=1;
    for(int a=0;a<100;a++){
        if(((rand() %(100-dificuldade)))==0){
            if((rand() %3)==1 && (a%(9+(10*(a/10))))!=0 && (a-90)<0 && caixas[a]==0 && caixas[a+1] == 0){
                caixas[a]=2;
                caixas[a+1]=9;
                caixas[a+10]=9;
                caixas[a+11]=9;
            }
            else if(rand() %3==2 && caixas[a]==0){
                caixas[a]=3;
            }
            
            else if(caixas[a]==0){
                caixas[a]=1;
            }
        }
    }       
}

int Desenha_caixas(int *caixas){
    int contador_de_caixas=0;
    float x=-5.5,y=0.5, z=-4.5;
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
                cubePosition.y = y;
                cubePosition.x = x;
                DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, WHITE);
                DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
            }
            else if(caixas[a]==2){
                contador_de_caixas++;
                cubePosition.z = z+0.5;
                cubePosition.y = y;
                cubePosition.x = x+0.5;
                DrawCube(cubePosition, 2.0f, 1.0f, 2.0f, WHITE);
                DrawCubeWires(cubePosition, 2.0f, 1.1f, 2.0f, BLACK);
            }
            else if(caixas[a]==3){
                contador_de_caixas+=2;
                cubePosition.z = z;
                cubePosition.y = y;
                cubePosition.x = x;
                DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, WHITE);
                DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
                cubePosition.y = y+1.1;
                DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, WHITE);
                DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
            }
            
        }
    return contador_de_caixas;
}

int Palpite_do_usuario(Sound *toque, Font *fonte, int dificuldade){
    int palpite=0;
    float tempo_inicial, tempo_atual;
    Vector2 palpite_posicao = {530.0f, 310.0f};
    
    tempo_inicial=GetTime();
    tempo_atual=GetTime();
    while((tempo_atual-tempo_inicial)<(1.0+(0.041*dificuldade)) && !WindowShouldClose()){
        tempo_atual=GetTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(490, 315, 220, 100, LIGHTGRAY);
        DrawTextEx(*fonte,TextFormat("Palpite: \n  %03i", palpite), palpite_posicao, 50, 2, BLACK);

        if (IsKeyPressed(KEY_W)){
            palpite++;
            SetSoundVolume(*toque, 1);
            PlaySound(*toque);
        }
        if (IsKeyPressed(KEY_S) && palpite!=0){
            palpite--;
            SetSoundVolume(*toque, 1);
            PlaySound(*toque);
        }
        EndDrawing(); 
    }
return palpite;
}

void Revela_cubos(int contador, int *caixas){
    float x=-5.5,y=0.5, z=-4.5;
    Vector3 cubePosition = { 0.0f, 0.5f, 0.0f };
    for(int a=0;a<contador;a++){
        x=x+1.0;
        if(a!=0 && a%10==0){
            x=-4.5;
            z=z+1.0;
        }
        if(caixas[a]==1){
            cubePosition.z = z;
            cubePosition.y = y;
            cubePosition.x = x;
            DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, RED);
            DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
        }
        else if(caixas[a]==2){
            cubePosition.z = z+0.5;
            cubePosition.y = y;
            cubePosition.x = x+0.5;
            DrawCube(cubePosition, 2.0f, 1.0f, 2.0f, BLUE);
            DrawCubeWires(cubePosition, 2.0f, 1.1f, 2.0f, BLACK);
        }
        else if(caixas[a]==3){
            cubePosition.z = z;
            cubePosition.y = y;
            cubePosition.x = x;
            DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, PURPLE);
            DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
            cubePosition.y = y+1.1;
            DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, PURPLE);
            DrawCubeWires(cubePosition, 1.0f, 1.1f, 1.0f, BLACK);
        }
    }
    
}

int Checa_palpite(int palpite, int *vidas, int quantidade_de_caixas, Sound *derrota, Sound *palmas, Sound *boo, Sound *vitoria){
    int pontos;
    if(quantidade_de_caixas==palpite){
        pontos=100;
        SetSoundVolume(*palmas, 0.5);
        SetSoundVolume(*vitoria, 0.5);
        PlaySound(*palmas);
        PlaySound(*vitoria);
    }
    else if(((quantidade_de_caixas-1)==palpite) || ((quantidade_de_caixas+1)==palpite)){
        pontos=50;
        for(int a=0;a<5;a++){
            if(vidas[a]==1){
                vidas[a]=0;
                SetSoundVolume(*derrota, 0.5);
                PlaySound(*derrota);
                break;
            }
        }
    }
    else{
        pontos=0;
        for(int a=0;a<5;a++){
            if(vidas[a]==1){
                vidas[a]=0;
                SetSoundVolume(*derrota, 0.5);
                SetSoundVolume(*boo, 0.4);
                PlaySound(*derrota);
                PlaySound(*boo);
                break;
            }
        }
    }
return pontos;    
}

int Checa_vida(int *vidas){
    for(int a=0;a<5;a++){
        if(vidas[a]==1){
            return 0;            
        }
    }
return 1;
}

void Desenha_status(int *vidas, int rodada, int pontos, Texture2D *vida_cheia, Texture2D *vida_vazia, Font *fonte){
    Vector2 vidas_posicao = {1050.0f, 400.0f};
    Vector2 pontos_posicao = {20.0f, 400.0f};
    Vector2 rodada_posicao = {530.0f, 40.0f};
    Vector2 quantidade_pontos = {80.0f, 440.0f};

    DrawRectangle(1000, 380, 250, 130, LIGHTGRAY);
    DrawRectangle(0, 380, 200, 130, LIGHTGRAY);
    
    DrawTextEx(*fonte,"VIDAS:",vidas_posicao, 40, 2, BLACK);
    DrawTextEx(*fonte,"PONTOS:",pontos_posicao, 40, 2, BLACK);
    DrawTextEx(*fonte,TextFormat("Rodada: %i", rodada), rodada_posicao, 40, 2, BLACK);
    DrawTextEx(*fonte,TextFormat("%i", pontos), quantidade_pontos, 40, 2, BLACK);
    
    for(int a=0;a<5;a++){
        if(vidas[a]==1){
            DrawTexture(*vida_cheia, (a*38)+1010, 450, WHITE);
        }
        else{
            DrawTexture(*vida_vazia, (a*38)+1010, 450, WHITE);
        }
    }
    
}   

void Mostra_cubos(Camera3D *camera, int *caixas){
    int contador=0;
    while(contador<101 && !WindowShouldClose()){
        contador++;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(*camera);
        Revela_cubos(contador, caixas);
        DrawGrid(10, 1.0f);
        EndMode3D();
        EndDrawing();
        WaitTime(0.04);
    }   
}



