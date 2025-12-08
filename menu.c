#include "raylib.h"
#include "string.h"
#include "stdio.h"


void carregarMenu(Music fundo, bool controleMusica);
void carregarInstrucao();
void fecharInstrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas, Music fundoTutorial);
void fecharMenu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play, Sound select1);
void menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play, Sound select1, bool controleMusica);
void instrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas, Music fundoTutorial);
void digitarNick(Font tahoma, Music FundoTutorial);
void carregarPlacar(Music fundo);
void tresdoisum(Font tahoma);
void registrarPlacar(char *nome, int pontuacao);

void main(void)
{
    InitWindow(1280, 720, "Consegue contar?");
    InitAudioDevice();
    SetTargetFPS(60);
    
    Music fundo = LoadMusicStream("sounds/Kevin MacLeod Pinball Spring - Kevin MacLeod Archive (youtube).mp3");
    carregarMenu(fundo, true);
}

void carregarMenu(Music fundo, bool controleMusica) {
    
    Texture2D botaoIniciar = LoadTexture("assets/botao_iniciar_spritesheet.png");
    Texture2D botaoPlacar = LoadTexture("assets/botao_placar_spritesheet.png");
    Texture2D botaoSair = LoadTexture("assets/botao_sair_spritesheet.png");
    Texture2D background = LoadTexture("assets/background_menu.png");
    Texture2D titulo = LoadTexture("assets/texto_principal_sprite.png");
    
    Sound HoverFinal = LoadSound("sounds/UI Hover - Sound Effect (HD) - Sound Library (youtube) (mp3cut.net).mp3");
    Sound play = LoadSound("sounds/SELECT Button Sound Effect - Brawl Stars - Sound Effects (youtube) (mp3cut.net).mp3");
    Sound select1 = LoadSound("sounds/Simple Game UI Sounds - SELECT1(mp3cut.net).mp3");
    
    menu(botaoIniciar, botaoPlacar, botaoSair, background, titulo, fundo, HoverFinal, play, select1, controleMusica);
    
}

void menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play, Sound select1, bool controleMusica){
    Rectangle Otitulo = {30, 120, 1583, 100};
    Rectangle iniciar = {480, 320, 320, 90};
    Rectangle placar = {482, 430, 320, 91};
    Rectangle sair = {530, 540, 200, 91};
    
    int controleHover [4] = {0, 0, 0, 0};
    int controleMenu [4] = {0, 0, 0, 0};
    
    if (controleMusica == true){
    PlayMusicStream(fundo);
    SetMusicVolume(fundo, 0.3);
    }
    
    int fechar = 0;
    
    while (true)
    {
        if (IsKeyPressed(KEY_ESCAPE) == true){
            fechar++;
        }
        if (IsKeyPressed(KEY_ESCAPE) == true && fechar == 2){
            break;
        }
        
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
                if (IsMouseButtonReleased(0) == true){
                        if (controleHover[2] == 1){
                        PlaySound(select1);
                        controleHover[2] = 2;
                    }
                    controleMenu[1] = 1;
                    break;
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
        UnloadMusicStream(fundo);
        carregarInstrucao();
    }
    if (controleMenu[1] == 1){
        controleMenu[1] = 0;
        fecharMenu;
        carregarPlacar(fundo);
    }
        CloseWindow(); 
}

void fecharMenu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play, Sound select1){
    UnloadTexture(botaoIniciar);
    UnloadTexture(botaoPlacar);
    UnloadTexture(botaoSair);
    UnloadTexture(background);
    UnloadTexture(titulo);

    UnloadSound(HoverFinal);
    UnloadSound(play);
    UnloadSound(select1);
}

void carregarInstrucao(){
    Font tahoma = LoadFontEx("assets/tahoma.ttf", 120, 0, 0);
    
    Texture2D background_instrucao = LoadTexture("assets/Instrucoes_background.png");
    Texture2D WS_transparente = LoadTexture("assets/botao_ws_transparente.png");
    Texture2D WS_pintado = LoadTexture("assets/botao_ws_pintado.png");
    Texture2D vidas = LoadTexture("assets/vidas_spritesheet_inplay.png");
    
    Music fundoTutorial = LoadMusicStream("sounds/Ghouls'n Ghosts (Arcade) Music- Stage Two.mp3");
    
    instrucao(tahoma, background_instrucao, WS_transparente, WS_pintado, vidas, fundoTutorial);
}

void instrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas, Music fundoTutorial){

    int controleFade = 0;
    int controleTutorial[] = {0, 0, 0, 0, 0};
    int tempo = 0;
    
    PlayMusicStream(fundoTutorial);
    SetMusicVolume(fundoTutorial, 0.3);
    
    while (!WindowShouldClose()){
        UpdateMusicStream(fundoTutorial);
        
        BeginDrawing();
            ClearBackground(WHITE);
            
            if (controleTutorial[4] == 0){
                DrawTextureV(background_instrucao, (Vector2){0, 0}, WHITE);
                DrawTextEx(tahoma, "Pressione ESC para pular", (Vector2){1090, 700}, 20, 0, BLACK);
                
            }
            else {
                if (controleFade > 1){
                DrawTextureV(background_instrucao, (Vector2){0, 0}, (Color){255, 255, 255, controleFade});
                DrawTextEx(tahoma, "Pressione ESC para pular", (Vector2){1090, 700}, 20, 0, (Color){0, 0, 0, controleFade});
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
                    if (tempo <= 120){
                    DrawTextEx(tahoma, " O JOGADOR DEVE CONTAR\n A QUANTIDADE DE CAIXAS\n  QUE APARECEM NA TELA", (Vector2){394, 320}, 50, 0, (Color){255, 255, 255, controleFade}); 
                    tempo++;}
                    else{
                    controleTutorial[0] = 1;}}
            }
            if (controleTutorial[0] == 1) {
                    DrawTextEx(tahoma, " O JOGADOR DEVE CONTAR\n A QUANTIDADE DE CAIXAS\n  QUE APARECEM NA TELA", (Vector2){394, 320}, 50, 0, (Color){255, 255, 255, controleFade}); 
                    controleFade -= 5;
                    if (controleFade == 0){
                        controleTutorial[0] = 2;
                        controleTutorial[1] = 1;
                        tempo = 0;
                    }
                    }
                
            if (controleTutorial[1] == 1){
                if (controleFade < 255){
                    controleFade += 5;
                    DrawTextEx(tahoma, " CADA ACERTO CONCEDE\nAO JOGADOR 100 PONTOS.\n\n CADA ERRO O JOGADOR\n     PERDE UMA VIDA.", (Vector2){410, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                }
                if (controleFade == 255) {
                    if (tempo <= 180){
                    DrawTextEx(tahoma, " CADA ACERTO CONCEDE\nAO JOGADOR 100 PONTOS.\n\n CADA ERRO O JOGADOR\n     PERDE UMA VIDA", (Vector2){410, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    tempo++;}
                    else{
                    controleTutorial[1] = 2;
                    tempo = 0;}
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
                    if (tempo <= 240){
                    DrawTextEx(tahoma, "VOCE TEM CINCO VIDAS\n\n  SE O JOGADOR ERRAR\n    POR POUCO AINDA\n    GANHA 50 PONTOS.", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTextureRec(vidas, (Rectangle){0, 0, 160, 33}, (Vector2){580, 350}, (Color){255, 255, 255, controleFade});
                    tempo++;}
                    else{
                    controleTutorial[2] = 2;
                    tempo = 0;}
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
                    if (tempo <= 180){
                    DrawTextEx(tahoma, "USE 'W' E 'S'\nPARA AJUSTAR\nA CONTAGEM\n\nBOA SORTE!", (Vector2){420, 290}, 50, 0, (Color){255, 255, 255, controleFade});
                    DrawTexture(WS_transparente, 750, 250, (Color){255, 255, 255, controleFade});
                    tempo++;}
                    else{
                controleTutorial[3] = 2;
                    tempo = 0;}
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
            fecharInstrucao(tahoma, background_instrucao, WS_transparente, WS_pintado, vidas, fundoTutorial);
            }
            
void fecharInstrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas, Music fundoTutorial){
    UnloadTexture(background_instrucao);
    UnloadTexture(WS_transparente);
    UnloadTexture(WS_pintado);
    UnloadTexture(vidas);
    
    
    digitarNick(tahoma, fundoTutorial);
}

void digitarNick(Font tahoma, Music fundoTutorial) {

    Texture2D background = LoadTexture("assets/nick_background.png");

    char nome[20] = "\0";
    int letras = 0;

    int fechar = 0;
    
    while (true) {
        if (IsKeyPressed(KEY_ESCAPE) == true){
            fechar++;
        }
        if (IsKeyPressed(KEY_ESCAPE) == true && fechar == 2){
            break;
        }
        UpdateMusicStream(fundoTutorial);
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letras < 19)) {
                nome[letras] = (char)key;
                letras++;
                nome[letras] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (letras > 0) {
                letras--;
                nome[letras] = '\0';
            }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureV(background, (Vector2){0,0}, WHITE);
            DrawTextEx(tahoma, nome, (Vector2){490, 330}, 40, 0, BLACK);
        EndDrawing();
    }

    UnloadMusicStream(fundoTutorial);
    UnloadTexture(background);
    tresdoisum(tahoma);

}

void tresdoisum(Font tahoma){
    
int tempo = 0;
Sound temporizador = LoadSound("sounds/3 2 1 0 Countdown With Sound Effect _ No Copyright _ Ready To Use.mp3");
PlaySound(temporizador);
while (tempo < 240){
    BeginDrawing();
        ClearBackground(WHITE);
        if (tempo <= 60){
        DrawTextEx(tahoma, "3", (Vector2){650, 300}, 90, 0, (Color){0, 122, 255, 255});
        tempo++;
        }
        if (tempo > 60 && tempo <= 120){
        DrawTextEx(tahoma, "2", (Vector2){650, 300}, 90, 0, (Color){0, 122, 255, 255});
        tempo++;
        }
        if (tempo > 120 && tempo <=180){
        DrawTextEx(tahoma, "1", (Vector2){650, 300}, 90, 0, (Color){0, 122, 255, 255});
        tempo++;
        }
        if (tempo > 180 && tempo < 240){
            DrawTextEx(tahoma, "GO!", (Vector2){620, 300}, 90, 0, (Color){0, 122, 255, 255});
        tempo++;
        }
        if (tempo == 239){
            break;
        }
        EndDrawing();
}

}

void carregarPlacar(Music fundo){
    Texture2D fundoPlacar = LoadTexture("assets/placar_background.png");
    
    FILE *placar = fopen("data/Placar.txt", "r");
    int total = 0;
    char nomes[10][20];
    int pontos[10];
    
    int altura = 200; 
   
    while (total < 10 && fscanf(placar, "%s %d", nomes[total], &pontos[total]) == 2){
        total++;
    }
    
    while (!WindowShouldClose()){
        UpdateMusicStream(fundo);
        BeginDrawing();
            DrawTexture(fundoPlacar, 0, 0, WHITE);
            for(int i = 0; i<total; i++){
                DrawText(nomes[i], 400, (altura + i*40), 32, WHITE);
                DrawText(TextFormat("%d", pontos[i]), 820, (altura + i*40), 32, WHITE);
            }
        EndDrawing();
    }
    UnloadTexture(fundoPlacar);
    carregarMenu(fundo, false);
}

void registrarPlacar(char *nome, int pontuacao) {
    
    char nomes[11][20] = {0};
    int pontos[11] = {0};
    int n = 0;
    
    FILE *f = fopen("data/Placar.txt", "r");
    
    if (f) {
        while (n < 10 && fscanf(f, "%s %d", nomes[n], &pontos[n]) == 2) {
            n++;
        }
        fclose(f);
    }
    
    int deveEntrar = 1;
    
    if (n == 10) {
        int menor = 0;
        for (int i = 1; i < n; i++) {
            if (pontos[i] < pontos[menor]) {
                menor = i;
            }
        }
        if (pontuacao <= pontos[menor]) {
            deveEntrar = 0;
        }
    }
    
    if (deveEntrar) {
        strcpy(nomes[n], nome);
        pontos[n] = pontuacao;
        n++; 
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (pontos[i] < pontos[j]) {
                    int temp = pontos[i];
                    pontos[i] = pontos[j];
                    pontos[j] = temp;
                    
                    char tempNome[20];
                    strcpy(tempNome, nomes[i]);
                    strcpy(nomes[i], nomes[j]);
                    strcpy(nomes[j], tempNome);
                }
            }
        }
        
        if (n > 10) {
            n = 10;
        }
        
        f = fopen("data/Placar.txt", "w");
        if (f) {
            for (int i = 0; i < n; i++) {
                fprintf(f, "%s %d\n", nomes[i], pontos[i]);
            }
            fclose(f);
        }
    }
}
