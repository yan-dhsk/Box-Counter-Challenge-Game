#include "raylib.h"
#include "string.h"
#include "stdio.h"
#include <time.h>
#include <stdlib.h>



void carregarMenu(Music fundo, bool controleMusica);
void carregarInstrucao();
void fecharInstrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas, Music fundoTutorial);
void fecharMenu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play, Sound select1);
void menu(Texture2D botaoIniciar, Texture2D botaoPlacar, Texture2D botaoSair, Texture2D background, Texture2D titulo, Music fundo, Sound HoverFinal, Sound play, Sound select1, bool controleMusica);
void instrucao(Font tahoma, Texture2D background_instrucao, Texture2D WS_transparente, Texture2D WS_pintado, Texture2D vidas, Music fundoTutorial);
void digitarNick(Font tahoma, Music FundoTutorial);
void carregarPlacar(Music fundo);
void tresdoisum(Font tahoma, char *nome);
void registrarPlacar(char *nome, int pontuacao);
void gameover(int deveEntrar, int pontuacao);

int inicioJogo(char *nome);
void Gera_numero_de_caixas(int dificuldade, int *caixas);
int Desenha_caixas(int *caixas);
int Palpite_do_usuario(Sound *toque, Font *fonte, int dificuldade);
void Revela_cubos(int contador, int *caixas);
int Checa_palpite(int palpite, int *vidas, int quantidade_de_caixas, Sound *derrota, Sound *palmas, Sound *boo, Sound *vitoria);
int Checa_vida(int *vidas);
void Desenha_status(int *vidas, int rodada, int pontos, Texture2D *vida_cheia, Texture2D *vida_vazia, Font *fonte);
void Mostra_cubos(Camera3D *camera, int *caixas);

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
        CloseAudioDevice();  
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
    tresdoisum(tahoma, nome);

}

void tresdoisum(Font tahoma, char *nome){
    
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

UnloadSound(temporizador);

BeginDrawing();
    ClearBackground(WHITE);
EndDrawing();

inicioJogo(nome);
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
    gameover(deveEntrar, pontuacao);
}

void gameover(int deveEntrar, int pontuacao){
    Texture2D background_gameover = LoadTexture("assets/game_over_background.png");
    Font tahoma = LoadFontEx("assets/tahoma.ttf", 120, 0, 0);
    Music game_over_placar = LoadMusicStream("sounds/Game Over Sound Effect (mp3cut.net).mp3");
    Music game_over = LoadMusicStream("sounds/Game Over (8-Bit Music).mp3");
    
    int controleFade = 0;
    int controleEstado = 0;
    int controleMusica = 0;
    
    while(true){
        if (IsKeyPressed(KEY_ESCAPE) == true || IsKeyPressed(KEY_ENTER) == true){
            break;
        }
        if (controleEstado == 0){
            controleFade += 15;
            if (controleFade == 255){
                controleEstado = 1;
        }
        }
        else if (controleEstado == 1){
            controleFade -= 15;
            if (controleFade == 0){
                controleEstado = 0;
            }
        }
        BeginDrawing();
            DrawTexture(background_gameover, 0, 0, (Color){255, 255, 255, controleFade});
            
            if (deveEntrar == 1){
                if (controleMusica == 0){
                    PlayMusicStream(game_over_placar);
                    controleMusica = 1;
                }
                else{
                    UpdateMusicStream(game_over_placar);
                }
                DrawTextEx(tahoma, "Pontos: ", (Vector2){520, 310}, 62, 0, (Color){0, 122, 255, controleFade});
                DrawTextEx(tahoma, TextFormat("%d", pontuacao), (Vector2){688, 310}, 62, 0, (Color){0, 122, 255, controleFade});
                DrawTextEx(tahoma, "Parabens! Voce esta no top 10!", (Vector2){470, 370}, 32, 0, (Color){0, 122, 255, controleFade});
            }
            else{
                if (controleMusica == 0){
                    PlayMusicStream(game_over);
                    controleMusica = 1;
            }
            else{
                UpdateMusicStream(game_over);
            }
            DrawTextEx(tahoma, "Pontos: ", (Vector2){520, 310}, 62, 0, (Color){0, 122, 255, controleFade});
            DrawTextEx(tahoma, TextFormat("%d", pontuacao), (Vector2){688, 310}, 62, 0, (Color){0, 122, 255, controleFade});
    }
    EndDrawing();
}

UnloadTexture(background_gameover);
UnloadMusicStream(game_over_placar);
UnloadMusicStream(game_over);
UnloadFont(tahoma);

Music fundo = LoadMusicStream("sounds/Kevin MacLeod Pinball Spring - Kevin MacLeod Archive (youtube).mp3");
carregarMenu(fundo, true);

}



int inicioJogo(char *nome){
    
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
    
    srand(time(NULL));
    
    int caixas[100], rodada=0, dificuldade=0, quantidade_de_caixas, palpite, vidas[]={1,1,1,1,1}, pontos=0, game_over=0;
    float tempo_atual, tempo_inicial;
    
    Texture2D vida_cheia=LoadTexture("assets/vida_cheia.png");
    Texture2D vida_vazia=LoadTexture("assets/vida_vazia.png");
    
    Font fonte=LoadFontEx("assets/tahoma.ttf", 120, 0, 0);
    
    Music musica_de_fundo=LoadMusicStream("sounds/Kevin MacLeod_ Blip Stream.mp3");
    Sound tambor=LoadSound("sounds/drum-roll-for-victory-366448.mp3");
    Sound derrota=LoadSound("sounds/derrota.mp3");
    Sound palmas=LoadSound("sounds/palmas.mp3");
    Sound booo=LoadSound("sounds/booo.mp3");
    Sound vitoria=LoadSound("sounds/vitoria.mp3");    
    Sound toque=LoadSound("sounds/toque.mp3");
    

    PlayMusicStream(musica_de_fundo);
    while(!WindowShouldClose()){
        rodada++;
        for(int x=0;x<100;x++){caixas[x]=0;} 
        if(dificuldade<95){
            dificuldade=35+(rodada*2);
        }
        SetMusicVolume(musica_de_fundo, 0.3);
        
        Gera_numero_de_caixas(dificuldade, caixas);
        
        BeginDrawing();
        ClearBackground(WHITE);
        
        Desenha_status(vidas, rodada, pontos, &vida_cheia, &vida_vazia, &fonte);
        
        BeginMode3D(camera);
        
        quantidade_de_caixas=Desenha_caixas(caixas);
        DrawGrid(10, 1.0f);
        
        EndMode3D();
        EndDrawing();
        
        tempo_inicial=GetTime();
        tempo_atual=GetTime();
        while((tempo_atual-tempo_inicial)<(2.4-(0.016*dificuldade)) && !WindowShouldClose()){
            UpdateMusicStream(musica_de_fundo);
            tempo_atual=GetTime();
        }
        
        palpite=0;
        float tempo_inicial_palpite=GetTime();
        float tempo_atual_palpite=GetTime();
        Vector2 palpite_posicao = {570.0f, 310.0f};
        
        while((tempo_atual_palpite-tempo_inicial_palpite)<(1.0+(0.041*dificuldade)) && !WindowShouldClose()){
            UpdateMusicStream(musica_de_fundo);
            tempo_atual_palpite=GetTime();
            BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangle(530, 315, 220, 100, LIGHTGRAY);
            DrawTextEx(fonte,TextFormat("Palpite: \n  %03i", palpite), palpite_posicao, 50, 2, BLACK);

            if (IsKeyPressed(KEY_W)){
                palpite++;
                SetSoundVolume(toque, 1);
                PlaySound(toque);
            }
            if (IsKeyPressed(KEY_S) && palpite!=0){
                palpite--;
                SetSoundVolume(toque, 1);
                PlaySound(toque);
            }
            EndDrawing(); 
        }
        
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
        if(game_over!=0){
            break;
            }

    }
StopMusicStream(musica_de_fundo);  
UnloadSound(toque);
UnloadSound(palmas);
UnloadSound(vitoria);
UnloadSound(derrota);
UnloadSound(booo);
UnloadSound(tambor);
UnloadMusicStream(musica_de_fundo);  
UnloadTexture(vida_cheia);
UnloadTexture(vida_vazia);
UnloadFont(fonte);

registrarPlacar(nome, pontos);
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
    Vector2 palpite_posicao = {570.0f, 310.0f};
    
    tempo_inicial=GetTime();
    tempo_atual=GetTime();
    while((tempo_atual-tempo_inicial)<(1.0+(0.041*dificuldade)) && !WindowShouldClose()){
        tempo_atual=GetTime();
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(530, 315, 220, 100, LIGHTGRAY);
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
    float scale_x = GetScreenWidth() / 1200.0f;
    float scale_y = GetScreenHeight() / 600.0f;

    Vector2 vidas_posicao = {1050.0f * scale_x, 400.0f * scale_y};
    Vector2 pontos_posicao = {20.0f * scale_x, 400.0f * scale_y};
    Vector2 rodada_posicao = {530.0f * scale_x, 40.0f * scale_y};
    Vector2 quantidade_pontos = {80.0f * scale_x, 440.0f * scale_y};

    DrawRectangle(1000 * scale_x, 380 * scale_y, 250 * scale_x, 130 * scale_y, LIGHTGRAY);
    DrawRectangle(0, 380 * scale_y, 200 * scale_x, 130 * scale_y, LIGHTGRAY);
    
    DrawTextEx(*fonte,"VIDAS:",vidas_posicao, 40, 2, BLACK);
    DrawTextEx(*fonte,"PONTOS:",pontos_posicao, 40, 2, BLACK);
    DrawTextEx(*fonte,TextFormat("Rodada: %i", rodada), rodada_posicao, 40, 2, BLACK);
    DrawTextEx(*fonte,TextFormat("%i", pontos), quantidade_pontos, 40, 2, BLACK);
    
    for(int a=0;a<5;a++){
        if(vidas[a]==1){
            DrawTexture(*vida_cheia, (a*38)*scale_x + 1010 * scale_x, 450 * scale_y, WHITE);
        }
        else{
            DrawTexture(*vida_vazia, (a*38)*scale_x + 1010 * scale_x, 450 * scale_y, WHITE);
        }
    }
}

void Mostra_cubos(Camera3D *camera, int *caixas){
    int contador=0;
    while(contador<101 && !WindowShouldClose()){
        contador++;
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(*camera);
        Revela_cubos(contador, caixas);
        DrawGrid(10, 1.0f);
        EndMode3D();
        EndDrawing();
        WaitTime(0.04);
    }   
}