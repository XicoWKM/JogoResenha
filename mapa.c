#include<string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#if defined (_WIN32)
# include <windows.h>
#elif defined (__unix__) || defined (__APPLE__)
# include <unistd.h>
# include <termios.h>
# include <sys/ioctl.h>
#endif
#define ESC "\033["


//serve para guardar as infrmações do terminal 
//retirado do codigo do nicolas jogo da velha
struct TerminalConfig
{
#if defined (_WIN32)
    UINT __output_codepage;
    UINT __codepage;
    DWORD __output_cfg;
    DWORD __input_cfg;
#elif defined (__unix__) || defined (__APPLE__)
    struct termios __input_cfg;
#endif
};
//infos do terminal
//parte do nicolas tambem
struct TerminalConfig original_terminal_cfg = {0};
//restaurar as informações do terminal
void restore_terminal(void)
{
    // Volta a mostrar o cursor.
    printf(ESC"?25h");
    // Volta para o buffer principal.
    printf(ESC"?1049l");

    // Aplicando as configurações originais do terminal.
#if defined (_WIN32)
    SetConsoleCP(original_terminal_cfg.__codepage);
    SetConsoleOutputCP(original_terminal_cfg.__output_codepage);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), original_terminal_cfg.__input_cfg);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), original_terminal_cfg.__output_cfg);
#elif defined (__unix__) || defined (__APPLE__)
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal_cfg.__input_cfg);
#endif
}

//confirguração do modo cru do sistema
//antes eu usava apenas o stty -icanon -echo, elel meio que ainda está aqui
//entretanto isso era limitado para o linux
// denovo com o codigo do nicolas posso fazer ser multiplataforma
void setup_terminal()
{
    // Aqui já precisamos fazer configurações
    // específicas para cada sistema.
#if defined (_WIN32)
    original_terminal_cfg.__output_codepage = GetConsoleOutputCP();
    original_terminal_cfg.__codepage = GetConsoleCP();

    // Dizendo ao terminal para utilizar utf-8
    // para não nos preocuparmos com caracteres especiais.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE stdout_h = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stdin_h = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(stdout_h, &original_terminal_cfg.__output_cfg);
    GetConsoleMode(stdin_h, &original_terminal_cfg.__input_cfg);

    DWORD stdout_mode = original_terminal_cfg.__output_cfg;
    DWORD stdin_mode = original_terminal_cfg.__input_cfg;

    // Precisamos informar ao terminal que
    // queremos ser capazes de utilizar as sequências ANSI
    // (as que começam com ESC).
    stdout_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    // Assim como queremos receber sequências ANSI como entrata também.
    stdin_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

    // Finalmente, colocamos a entrada no "modo cru".
    stdin_mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);

    SetConsoleMode(stdout_h, stdout_mode);
    SetConsoleMode(stdin_h, stdin_mode);
#elif defined (__unix__) || defined (__APPLE__)
    tcgetattr(STDIN_FILENO, &original_terminal_cfg.__input_cfg);

    struct termios stdin_trms = original_terminal_cfg.__input_cfg;
    // Colocando a entrada no "modo cru".
    stdin_trms.c_lflag &= ~(ECHO | ICANON | ISIG);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &stdin_trms);
#endif    
    // Tiramos a bufferização da saída
    // para não precisarmos ter que usar `\n`
    // e nem usar `fflush`.
    // Não é bom para performance
    // mas deixa as coisas mais simples.
    setvbuf(stdout, NULL, _IONBF, 0);

    // Muda para o buffer alternativo.
    printf(ESC"?1049h");
    // Esconde o cursor.
    printf(ESC"?25l");

    // Quando o programa fechar
    // `restore_terminal` vai ser chamado
    // e fazer o terminal voltar ao
    // normal.
    atexit(restore_terminal);
}


//meu codigo 
int printMovimento(int mapa[15][15],int pscJog[]){
  int mov = 0;
  //movimento y
    //cima
    if(mapa[pscJog[0]-1][pscJog[1]] != 1 && mapa[pscJog[0]-1][pscJog[1]] != 5)
        mov += 1;
    //fbaixo
    if(mapa[pscJog[0]+1][pscJog[1]] != 1 && mapa[pscJog[0]+1][pscJog[1]] != 5)
        mov += 2;
  //movimento x
    //direita
    if(mapa[pscJog[0]][pscJog[1]+1] != 1 && mapa[pscJog[0]][pscJog[1]+1] != 5)
       mov += 4;
    //esquerda
    if(mapa[pscJog[0]][pscJog[1]-1] != 1 && mapa[pscJog[0]][pscJog[1]-1] != 5)
       mov += 8;
    
  return mov;
}

int movimento(int mov,int pscJog[],int mapaJogador[15][15]){
  //tranformar o int em um numero binario
  bool binario[4];
  for(int i=0;i<4;i++){ 
    binario[i] = (bool) (mov%2);
    mov = mov/2;
  } 
//onde o jogador quer ir e verificar se é possivel
  int opt;
   opt = fgetc(stdin);
  //cima
  if(opt == 'w' && binario[0] == 1){
    pscJog[0] = pscJog[0] - 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    return 0;
  }
  //baixo
  else if(opt == 's' && binario[1] == 1){
    pscJog[0] = pscJog[0] + 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    return 0;
  }
  //direita
  else if(opt == 'd' && binario[2] == 1){
    mapaJogador[pscJog[0]][pscJog[1]] = 0;
    pscJog[1] = pscJog[1] + 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    return 0;
  }
  //esquerda
  else if(opt == 'a' && binario[3] == 1){
    pscJog[1] = pscJog[1] - 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    return 0;
  }
  else if(opt == 'q')
    return 1;

}

void printMapa(int mapaJogador[15][15],int pscJog[],int mapa[15][15]){
   mapaJogador[pscJog[0]][pscJog[1]] = 2;
   mapaJogador[pscJog[0]-1][pscJog[1]] = mapa[pscJog[0]-1][pscJog[1]];
   mapaJogador[pscJog[0]+1][pscJog[1]] = mapa[pscJog[0]+1][pscJog[1]];
   mapaJogador[pscJog[0]][pscJog[1]+1] = mapa[pscJog[0]][pscJog[1]+1];
   mapaJogador[pscJog[0]][pscJog[1]-1] = mapa[pscJog[0]][pscJog[1]-1];
  // #if defined(__unix__) || defined (__APPLE__)
  //  system("clear");
  // #elif defined(__WIN32)
  //   system("CLS");
  // #endif 
  printf(ESC"1J");
  printf(ESC"H");

  for(int y=0;y<15;y++){
    for(int x=0;x<15;x++){
      if(mapaJogador[y][x] == 6)
        printf(ESC"38;5;8m\u2588\u2588");
      else if(mapaJogador[y][x] == 5)
        printf(ESC"38;5;0m\u2588\u2588");
      else if(mapaJogador[y][x] == 2)
        printf(ESC"38;5;4m\u2588\u2588");
      else if(mapaJogador[y][x] == 0)
        printf(ESC"38;5;22m\u2588\u2588");
      else if(mapaJogador[y][x] == 1)
        printf(ESC"38;5;1m\u2588\u2588");
      else if(mapaJogador[y][x] == 7)
        printf(ESC"38;5;3m\u2588\u2588");
    }
    printf("\n");
  }
}
bool verificadorVitoria(int pscJog[], int mapa[15][15]){
  if(mapa[pscJog[0]][pscJog[1]] == 7)
   return true;
  else
    return false; 
}

int main(){
  printf(ESC"=19h");
  setup_terminal();
 // system("stty -icanon -echo");
  int pscJog[2] = {1,1};
  int mapaJogador [15][15];
  int mapa[15][15] = {
      {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
      {5,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
      {5,0,1,1,1,0,0,0,1,1,1,0,0,0,5},
      {5,0,0,0,0,0,1,0,0,0,1,0,1,0,5},
      {5,0,1,0,1,0,1,1,1,0,1,0,1,0,5},
      {5,0,0,0,1,0,0,0,1,0,0,0,1,0,5},
      {5,1,1,0,1,1,1,0,1,1,1,0,1,0,5},
      {5,0,0,0,0,0,0,0,0,0,1,0,0,0,5},
      {5,0,1,1,1,1,1,0,1,0,1,1,1,0,5},
      {5,0,0,0,0,0,1,0,1,0,0,0,1,0,5},
      {5,1,1,1,1,0,1,0,1,1,1,0,1,0,5},
      {5,0,0,7,1,0,0,0,0,0,1,0,0,0,5},
      {5,0,1,0,1,1,1,1,1,0,1,1,1,0,5},
      {5,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
      {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
  };
  
  for(int c1=0;c1<15;c1++){
    for(int c2=0;c2<15;c2++)
      mapaJogador[c1][c2] = 6;
  }
  int mov;

  while(1){
    
    printMapa(mapaJogador,pscJog,mapa);
    mov = printMovimento(mapa,pscJog);
    printf("\n");
    char quit=movimento(mov,pscJog,mapaJogador);
    //verificador para fechar o jogo
    if(quit == 1){
    //  system("stty sane");
      restore_terminal();
      printf(ESC"1m\n****JOGO FECHADO***\n");
      return 0;
    }
    if(verificadorVitoria(pscJog,mapa) == true){
      printMapa(mapaJogador,pscJog,mapa);
      printf(ESC"1m\n***VOCE VENCEU***\n");
      restore_terminal();
     // system("stty sane");
      return 0;
    }
  }
  
}

