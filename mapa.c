#include<stdio.h>
#include<string.h>

//variavel global da posiçaõ do jogador e do mapa
int pscJog[2] = {2,2};

int mapa[15][15] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,0,0,1,1,1,0,0,0,1},
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
    {1,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void movimento(int *mapa){
  //movimento y
    //atras
    if(mapa[pscJog[0]][pscJog-1] == 1 )
      printf("\nAtras bloqueada");
    else if(mapa[pscJog[0]][pscJog-1] == 0 )
     printf("\nAtras livre");
    //frente
    if(mapa[pscJog[0]][pscJog+1] == 1 )
      printf("\nFrente bloqueada");
    else if(mapa[pscJog[0]][pscJog+1] == 0 )
      printf("\nFrente livre");
}


int main(){

}