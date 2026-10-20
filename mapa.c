#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#define ESC "\033["

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
  system("stty -icanon -echo");
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
      system("stty sane");
      printf(ESC"1m\n****JOGO FECHADO***\n");
      return 0;
    }
    if(verificadorVitoria(pscJog,mapa) == true){
      printMapa(mapaJogador,pscJog,mapa);
      printf(ESC"1m\n***VOCE VENCEU***\n");
      system("stty sane");
      return 0;
    }
  }
  
}

