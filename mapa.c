#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

//variavel global da posiçaõ do jogador e do mapa
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



int printMovimento(){
  int mov = 0;
  //movimento y
    //cima
    if(mapa[pscJog[0]-1][pscJog[1]] != 1 && mapa[pscJog[0]-1][pscJog[1]] != 5){
    // printf("\nCima livre");
      mov += 1;
    }
    // else if(mapa[pscJog[0]-1][pscJog[1]] == 1 )
    //   printf("\nCima bloqueada");
    //fbaixo
    if(mapa[pscJog[0]+1][pscJog[1]] != 1 && mapa[pscJog[0]+1][pscJog[1]] != 5){
     // printf("\nBaixo livre");
      mov += 2;
    }
    // else if(mapa[pscJog[0]+1][pscJog[1]] == 1 )
    //   printf("\nBaixo bloqueada");
//movimento x
    //direita
    if(mapa[pscJog[0]][pscJog[1]+1] != 1 && mapa[pscJog[0]][pscJog[1]+1] != 5){
    //  printf("\nDireita livre");
       mov += 4;
    }
    // else if(mapa[pscJog[0]][pscJog[1]+1] == 1 )
    //  printf("\nDireita bloqueada");
    //esquerda
    if(mapa[pscJog[0]][pscJog[1]-1] != 1 && mapa[pscJog[0]][pscJog[1]-1] != 5){
    //  printf("\nEsquerda livre");
     mov += 8;
    }
    // else if(mapa[pscJog[0]][pscJog[1]-1] == 1 )
    // /  printf("\nEsquerda bloqueada");

  return mov;
}

void movimento(int mov){
  //tranformar o int em um numero binario
  bool binario[4];
  for(int i=0;i<4;i++){ 
    binario[i] = (bool) (mov%2);
    mov = mov/2;
    //printf("%d\t",binario[i]);
  } 
  //onde o jogador quer ir e verificar se é possivel
  int opt;
 //+printf("\nPara onde queres ir?:\n1. Cima\n2. Baixo\n3. Direita\n4. Esquerda");
   opt = fgetc(stdin);
   //opt -= 0x30;
  //cima
  if(opt == 'w' && binario[0] == 1){
    mapaJogador[pscJog[0]][pscJog[1]] = 0;
    pscJog[0] = pscJog[0] - 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    //printf("\nPosicao do jogador x = %d e y = %d",pscJog[0],pscJog[1]);
  }
  //baixo
  else if(opt == 's' && binario[1] == 1){
    mapaJogador[pscJog[0]][pscJog[1]] = 0;
    pscJog[0] = pscJog[0] + 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    //printf("\nPosicao do jogador x = %d e y = %d",pscJog[0],pscJog[1]);
  }
  //direita
  else if(opt == 'd' && binario[2] == 1){
    mapaJogador[pscJog[0]][pscJog[1]] = 0;
    pscJog[1] = pscJog[1] + 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    //printf("\nPosicao do jogador x = %d e y = %d",pscJog[0],pscJog[1]);
  }
  //esquerda
  else if(opt == 'a' && binario[3] == 1){
    mapaJogador[pscJog[0]][pscJog[1]] = 0;
    pscJog[1] = pscJog[1] - 1;
    mapaJogador[pscJog[0]][pscJog[1]] = 2;
    //printf("\nPosicao do jogador x = %d e y = %d",pscJog[1],pscJog[0]);
  }
  else{
    //printf("***Opcao invalida***\nPosicao do jogador x = %d e y = %d",pscJog[0],pscJog[1]);
  }

}

void printMapa(){
   mapaJogador[pscJog[0]][pscJog[1]] = 2;
   mapaJogador[pscJog[0]-1][pscJog[1]] = mapa[pscJog[0]-1][pscJog[1]];
   mapaJogador[pscJog[0]+1][pscJog[1]] = mapa[pscJog[0]+1][pscJog[1]];
   mapaJogador[pscJog[0]][pscJog[1]+1] = mapa[pscJog[0]][pscJog[1]+1];
   mapaJogador[pscJog[0]][pscJog[1]-1] = mapa[pscJog[0]][pscJog[1]-1];
  #if defined(__unix__) || defined(__APPLE__)
      system("clear");
  #elif defined(_WIN32)
      system("CLS");
  #endif
  for(int y=0;y<15;y++){
    for(int x=0;x<15;x++){
      if(mapaJogador[y][x] == 6)
        printf("\033[38;5;8m\u2588\u2588 \033[0m");
      else if(mapaJogador[y][x] == 5)
        printf("\033[38;5;0m\u2588\u2588 \033[0m");
      else if(mapaJogador[y][x] == 2)
        printf("\033[38;5;4m\u2588\u2588 \033[0m");
      else if(mapaJogador[y][x] == 0)
        printf("\033[38;5;22m\u2588\u2588 \033[0m");
      else if(mapaJogador[y][x] == 1)
        printf("\033[38;5;1m\u2588\u2588 \033[0m");
      else if(mapaJogador[y][x] == 7)
        printf("\033[38;5;3m\u2588\u2588 \033[0m");
    }
    printf("\n");
  }
}
bool verificadorVitoria(){
  if(mapa[pscJog[0]][pscJog[1]] == 7)
   return true;
  else
    return false; 
}
int main(){
  #if defined(__unix__) || defined(__APPLE__)
    system("stty -icanon -echo");
  #endif
  for(int c1=0;c1<15;c1++){
    for(int c2=0;c2<15;c2++)
      mapaJogador[c1][c2] = 6;
  }
  int mov;

  while(1){
    printMapa();
    mov = printMovimento();
    printf("\n");
    movimento(mov);
    if(verificadorVitoria() == true){
       printMapa();
       printf("\n***VOCE VENCEU***");
       system("stty sane");
      return 0;
    }
  }
  
}

