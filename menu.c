#include "raylib.h"

int menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music ndo, Sound HoverFinal, Sound play);

void main(void)
{
    InitWindow(1280, 720, "Consegue contar?");
    InitAudioDevice();
    SetTargetFPS(60);
    
    Texture2D botaoIniciar = LoadTexture("assets/botao_iniciar_spritesheet.png");
    Texture2D botaoPlacar = LoadTexture("assets/botao_placar_spritesheet.png");
    Texture2D botaoSair = LoadTexture("assets/botao_sair_spritesheet.png");
    Texture2D background = LoadTexture("assets/background_menu.png");
    Texture2D titulo = LoadTexture("assets/texto_principal_sprite.png");
    
    Music fundo = LoadMusicStream("sounds/Kevin MacLeod Pinball Spring - Kevin MacLeod Archive (youtube).mp3");
    
    Sound HoverFinal = LoadSound("sounds/UI Hover - Sound Effect (HD) - Sound Library (youtube) (mp3cut.net).mp3");
    Sound play = LoadSound("sounds/SELECT Button Sound Effect - Brawl Stars - Sound Effects (youtube) (mp3cut.net).mp3");
    
    menu(botaoIniciar, botaoPlacar, botaoSair, background, titulo, fundo, HoverFinal, play);

    
}

int menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play){
    Rectangle Otitulo = {30, 120, 1583, 100};
    Rectangle iniciar = {480, 320, 320, 90};
    Rectangle placar = {482, 430, 320, 91};
    Rectangle sair = {530, 540, 200, 91};
    
    int controleHover [4] = {0, 0, 0, 0};
    
    PlayMusicStream(fundo);
    SetMusicVolume(fundo, 0.5);
    
    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool mouseClick = IsMouseButtonDown(0);
        
        UpdateMusicStream(fundo);
        BeginDrawing();
        
            ClearBackground(WHITE);
            DrawTextureV(background, (Vector2){ 0, 0 }, WHITE);
            if (CheckCollisionPointRec(mouse, Otitulo) == false){
                DrawTextureRec(titulo, (Rectangle){0, 180, 1583, 200}, (Vector2){30, 65}, WHITE);
            }
            else {
                DrawTextureRec(titulo, (Rectangle){0, 0, 1583, 200}, (Vector2){18, 80}, WHITE);
                
            }
            if (CheckCollisionPointRec(mouse, iniciar) == false){
                DrawTextureRec(botaoIniciar, (Rectangle){0, 0, 320, 90}, (Vector2){480, 320}, WHITE);
                controleHover[0] = 0;
                controleHover[1] = 0;
            }
            else{
                if (controleHover[1] == 0){
                    PlaySound(HoverFinal);
                    controleHover[1] = 1;
                }
                if (mouseClick == true){
                    DrawTextureRec(botaoIniciar, (Rectangle){0, 189, 320, 100}, (Vector2){480, 320}, WHITE);
                }
                else{
                    DrawTextureRec(botaoIniciar, (Rectangle){0, 91, 320, 100}, (Vector2){480, 320}, WHITE);
                }
                if (IsMouseButtonReleased(0) == true){
                        if (controleHover[0] == 0){
                        PlaySound(play);
                        controleHover[0] = 1;
                    }
                }
            }
            if (CheckCollisionPointRec(mouse, placar) == false){
                DrawTextureRec(botaoPlacar, (Rectangle){0, 0, 320, 91}, (Vector2){482, 430}, WHITE);
                controleHover[2] = 0;
            }
            else{
                if (controleHover[2] == 0){
                    PlaySound(HoverFinal);
                    controleHover[2] = 1;
                }
                if (mouseClick == true){
                    DrawTextureRec(botaoPlacar, (Rectangle){0, 187, 314, 96}, (Vector2){482, 430}, WHITE);
                }
                else{
                    DrawTextureRec(botaoPlacar, (Rectangle){0, 91, 314, 96}, (Vector2){482, 430}, WHITE);
                }
            }
            if (CheckCollisionPointRec(mouse, sair) == false){
                DrawTextureRec(botaoSair, (Rectangle){0, 0, 200, 91}, (Vector2){530, 540}, WHITE);
                controleHover[3] = 0;
            }
            else{
                if (controleHover[3] == 0){
                    PlaySound(HoverFinal);
                    controleHover[3] = 1;
                }
                if (mouseClick == true){
                    DrawTextureRec(botaoSair, (Rectangle){0, 190, 209, 100}, (Vector2){530, 540}, WHITE);
                    
                }
                else {
                    DrawTextureRec(botaoSair, (Rectangle){0, 91, 209, 100}, (Vector2){530, 540}, WHITE);
                }
                if (IsMouseButtonReleased(0) == true){
                        break;
                    }
    }
        EndDrawing();
    }

    CloseWindow();   
    return 0;
}