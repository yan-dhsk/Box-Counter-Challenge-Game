#include "raylib.h"

void carregarMenu();
void carregarInstrucao();
void fecharInstrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas);
void fecharMenu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play);
void menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music ndo, Sound HoverFinal, Sound play);
void instrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas);

void main(void)
{
    InitWindow(1280, 720, "Consegue contar?");
    InitAudioDevice();
    SetTargetFPS(60);
    
    carregarMenu();
}

void carregarMenu() {
    
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

void menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play){
    Rectangle Otitulo = {30, 120, 1583, 100};
    Rectangle iniciar = {480, 320, 320, 90};
    Rectangle placar = {482, 430, 320, 91};
    Rectangle sair = {530, 540, 200, 91};
    
    int controleHover [4] = {0, 0, 0, 0};
    int controleMenu [4] = {0, 0, 0, 0};
    
    PlayMusicStream(fundo);
    SetMusicVolume(fundo, 0.4);
    
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
                    controleMenu[0] = 1;
                    break;
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
    if (controleMenu[0] == 1){
        controleMenu[0] = 0;
        fecharMenu;
        carregarInstrucao();
    }
        CloseWindow(); 
}

void fecharMenu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play){
    UnloadTexture(botaoIniciar);
    UnloadTexture(botaoPlacar);
    UnloadTexture(botaoSair);
    UnloadTexture(background);
    UnloadTexture(titulo);
    UnloadMusicStream(fundo);
    UnloadSound(HoverFinal);
    UnloadSound(play);
}

void carregarInstrucao(){
    Font tahoma = LoadFontEx("assets/tahoma.ttf", 120, 0, 0);
    
    Texture2D background_instrucao = LoadTexture("assets/Instrucoes_background.png");
    Texture2D WS_transparente = LoadTexture("assets/botao_ws_transparente.png");
    Texture2D WS_pintado = LoadTexture("assets/botao_ws_pintado.png");
    Texture2D vidas = LoadTexture("assets/vidas_spritesheet_inplay.png");
    
    instrucao(tahoma, background_instrucao, WS_transparente, WS_pintado, vidas);
}

void instrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas){

    int controleFade = 0;
    int controleTutorial[] = {0, 0, 0, 0, 0};
    
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);
            
            if (controleTutorial[4] == 0){
                DrawTextureV(background_instrucao, (Vector2){0, 0}, WHITE);
            }
            else {
                if (controleFade > 1){
                DrawTextureV(background_instrucao, (Vector2){0, 0}, (Color){255, 255, 255, controleFade});
                controleFade -= 5;}
                else if (controleFade == 0) {
                    break;
                }
            }                
           
            if (controleTutorial[0] == 0){
                if (controleFade < 255){
                    controleFade += 5;
                    DrawTextEx(tahoma, " O JOGADOR DEVE CONTAR\n A QUANTIDADE DE CAIXAS\n  QUE APARECEM NA TELA", (Vector2){394, 320}, 50, 0, (Color){255, 255, 255, controleFade});  
                }
                if (controleFade == 255){
                    DrawTextEx(tahoma, " O JOGADOR DEVE CONTAR\n A QUANTIDADE DE CAIXAS\n  QUE APARECEM NA TELA", (Vector2){394, 320}, 50, 0, (Color){255, 255, 255, controleFade}); 
                    WaitTime(2);
                    controleTutorial[0] = 1;}
            }
            if (controleTutorial[0] == 1) {
                    DrawTextEx(tahoma, " O JOGADOR DEVE CONTAR\n A QUANTIDADE DE CAIXAS\n  QUE APARECEM NA TELA", (Vector2){394, 320}, 50, 0, (Color){255, 255, 255, controleFade}); 
                    controleFade -= 5;
                    if (controleFade == 0){
                        controleTutorial[0] = 2;
                        controleTutorial[1] = 1;
                    }
                    }
                
            if (controleTutorial[1] == 1){
                if (controleFade < 255){
                    controleFade += 5;
                    DrawTextEx(tahoma, " CADA ACERTO CONCEDE\nAO JOGADOR 100 PONTOS.\n\n CADA ERRO O JOGADOR\n     PERDE UMA VIDA.", (Vector2){410, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                }
                if (controleFade == 255) {
                    DrawTextEx(tahoma, " CADA ACERTO CONCEDE\nAO JOGADOR 100 PONTOS.\n\n CADA ERRO O JOGADOR\n     PERDE UMA VIDA", (Vector2){410, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    WaitTime(3);
                    controleTutorial[1] = 2;
                }
                
            }
            
            if (controleTutorial[1] == 2){
                if (controleFade > 1){
                    controleFade -= 5;
                    DrawTextEx(tahoma, " CADA ACERTO CONCEDE\nAO JOGADOR 100 PONTOS.\n\n CADA ERRO O JOGADOR\n     PERDE UMA VIDA.", (Vector2){410, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                }
                if (controleFade == 0){
                    controleTutorial[1] = 3;
                    controleTutorial[2] = 1;
                }
            }
            
            if (controleTutorial[2] == 1){
                if (controleFade < 255){
                    controleFade += 5;
                    DrawTextEx(tahoma, "VOCE TEM CINCO VIDAS\n\n  SE O JOGADOR ERRAR\n    POR POUCO AINDA\n    GANHA 50 PONTOS.", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTextureRec(vidas, (Rectangle){0, 0, 160, 33}, (Vector2){580, 350}, (Color){255, 255, 255, controleFade});
                }
                if (controleFade == 255){
                    DrawTextEx(tahoma, "VOCE TEM CINCO VIDAS\n\n  SE O JOGADOR ERRAR\n    POR POUCO AINDA\n    GANHA 50 PONTOS.", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTextureRec(vidas, (Rectangle){0, 0, 160, 33}, (Vector2){580, 350}, (Color){255, 255, 255, controleFade});
                    WaitTime(4);
                    controleTutorial[2] = 2;
                }}
            if (controleTutorial[2] == 2){
                if (controleFade > 1){
                    controleFade -=5;
                    DrawTextEx(tahoma, "VOCE TEM CINCO VIDAS\n\n  SE O JOGADOR ERRAR\n    POR POUCO AINDA\n    GANHA 50 PONTOS.", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTextureRec(vidas, (Rectangle){0, 0, 160, 33}, (Vector2){580, 350}, (Color){255, 255, 255, controleFade});
                }
                if (controleFade == 0){
                controleTutorial[2] = 3;
                controleTutorial[3] = 1;
                }
            }
            if (controleTutorial[3] == 1){
                if (controleFade < 255){
                    controleFade +=5;
                    DrawTextEx(tahoma, "USE 'W' E 'S'\nPARA AJUSTAR\nA CONTAGEM\n\nBOA SORTE!", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTexture(WS_transparente, 750, 250, (Color){255, 255, 255, controleFade});
                }
                if (controleFade == 255){
                    DrawTextEx(tahoma, "USE 'W' E 'S'\nPARA AJUSTAR\nA CONTAGEM\n\nBOA SORTE!", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTexture(WS_transparente, 750, 250, (Color){255, 255, 255, controleFade});
                    WaitTime(3);
                controleTutorial[3] = 2;
                }
            }
            
            if (controleTutorial[3] == 2){
                if (controleFade > 1){
                    controleFade -=5;
                    DrawTextEx(tahoma, "USE 'W' E 'S'\nPARA AJUSTAR\nA CONTAGEM\n\nBOA SORTE!", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTexture(WS_transparente, 750, 250, (Color){255, 255, 255, controleFade});
                }
                
                if (controleFade == 0){
                    controleTutorial[3] = 3;
                    controleTutorial[4] = 1;
                    controleFade = 255;
                    
                }
            }
            
            
               EndDrawing(); 
                }
            fecharInstrucao(tahoma, background_instrucao, WS_transparente, WS_pintado, vidas);
            }
            
void fecharInstrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas){
    UnloadFont(tahoma);
    UnloadTexture(background_instrucao);
    UnloadTexture(WS_transparente);
    UnloadTexture(WS_pintado);
    UnloadTexture(vidas);
    carregarMenu();
}
        
