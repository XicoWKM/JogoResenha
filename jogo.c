#include<stdio.h>
#include<time.h>
#include<stdlib.h>



//personagem do jogador
typedef struct boneco{
    int vida;
    int ataque;
    int habilidade[4];
} boneco;

void defineBoneco(boneco *personagens, int VD, int AT) {
    personagens->vida = VD;
    personagens->ataque = AT;
}  

void combate(boneco *jogador, boneco *inimigo,int *fim){
int opt;
    system("clear");
    printf("Vida Jogador: %d             Vida Inimigo: %d\n",jogador->vida,inimigo->vida);
    //ações jogador
        printf("\no que deseja fazer?:\n1. Ataque   2.Habilidade");
         scanf("%d",&opt);
        switch(opt){
            case 1:
                inimigo->vida = inimigo->vida - jogador->ataque;
                  printf("Voce causou %d de dano\n", jogador->ataque);
                break;
            case 2:
            printf("ola");
                break;
        }
    //ações inimmigo
    int chance = rand()%2;
        switch(chance){
                case 0:
                    jogador->vida = jogador->vida - inimigo->ataque;
                    printf("Voce tomou %d de dano\n",inimigo->ataque);
                    break;
                case 1:
                    printf("O inimigo errou o ataque\n");
                    break;
            }
        printf("\nPressione Enter para continuar...\n");
         while(getchar() != '\n');
         getchar();
        if(inimigo->vida <= 0){
            printf("\n***voce ganhou***\n");
            *fim = 1;
        }
        else if(jogador->vida <= 0){
            printf("\n***voce perdeu***\n");
            *fim = 2;
        }
}

int main(){
//inicializa o randomizador e variavel para o fim das batalhas
int fim=0;
srand(time(NULL));
//personagens
boneco jogador;
boneco inimigo;
    defineBoneco(&jogador,30,5);
    defineBoneco(&inimigo,40,4);
//combate
    while(fim == 0)   
        combate(&jogador,&inimigo,&fim);

        printf("\n%d\n",fim);
return 0;
}