#include<stdio.h>
#include<string.h>

//variavel global da posiçaõ do jogador e do mapa
int pscJog[2] = {2,2};

 int mapa[15][15] = {
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,1,1,1,1,0,0,0,1,1,1,0,0,0,1},
     {1,0,1,0,0,0,1,0,0,0,1,0,1,0,1},
     {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
     {1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
     {1,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
     {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1},
     {1,0,0,0,0,0,1,0,1,0,0,0,1,0,1},
     {1,1,1,1,1,0,1,0,1,1,1,0,1,0,1},
     {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
     {1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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


int main(){
  int mov;
  mov = printMovimento();
  printf("\n%d",mov);
}