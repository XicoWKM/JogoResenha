#include<stdio.h>
#include<string.h>
#include <stdbool.h>

//variavel global da posiçaõ do jogador e do mapa
int pscJog[2] = {2,2};
int mapa[15][15] = {
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,0,1,1,1,0,0,0,1,1,1,0,0,0,1},
     {1,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
     {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
     {1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
     {1,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
     {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1},
     {1,0,0,0,0,0,1,0,1,0,0,0,1,0,1},
     {1,1,1,1,1,0,1,0,1,1,1,0,1,0,1},
     {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
     {1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
 };

int printMovimento(){
  int mov = 0;
  //movimento y
    //atras
    if(mapa[pscJog[0]][pscJog[1]-1] == 0 ){
      printf("\nAtras livre");
      mov += 1;
    }
    else if(mapa[pscJog[0]][pscJog[1]-1] == 1 )
      printf("\nAtras bloqueada");
    //frente
    if(mapa[pscJog[0]][pscJog[1]+1] == 0 ){
      printf("\nFrente livre");
      mov += 2;
    }
    else if(mapa[pscJog[0]][pscJog[1]+1] == 1 )
      printf("\nFrente bloqueada");
//movimento x
    //atras
    if(mapa[pscJog[0]-1][pscJog[1]] == 0 ){
      printf("\nDireita livre");
       mov += 4;
    }
    else if(mapa[pscJog[0]-1][pscJog[1]] == 1 )
     printf("\nDireita bloqueada");
    //frente
    if(mapa[pscJog[0]+1][pscJog[1]] == 0 ){
      printf("\nEsquerda livre");
     mov += 8;
    }
    else if(mapa[pscJog[0]+1][pscJog[1]] == 1 )
      printf("\nEsquerda bloqueada");

  return mov;
}

void movimento(int mov){
  //tranformar o int em um numero binario
  bool binario[4];
  for(int i=0;i<4;i++){ 
    binario[i] = (bool) (mov%2);
    mov = mov/2;
    printf("%d\t",binario[i]);
  } 
  //onde o jogador quer ir e verificar se é possivel
  int opt;
  printf("\nPara onde queres ir?: ");
   scanf("%d",&opt);


  
}

int main(){
  int mov;
  mov = printMovimento();
  printf("\n");
  movimento(mov);
}

