//DANIEL SANTOS SOUZA RA:200387 
//GABRIEL LUCAS PINHEIRO DE ARRUDA RA:200840

#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>

void main(){

    float *x,*fx,valorDoX,contaCima,contaBaixo,resposta=0.0;
    int pontos,i,j,c=0;
    int verifica=1;
    char escolha;

    printf("\nDigite a quantidade de pontos:");
    scanf("%d",&pontos);


    x=(float *)malloc(pontos * sizeof(float));
    fx=(float *)malloc(pontos * sizeof(float));


    for(i=0;i<pontos;i++){

        printf("\nDigite o valor de x:");
        scanf("%f",(x + i));
        printf("\nDigite o valor de f(x):");
        scanf("%f",(fx + i));
    }

   
    
    while (verifica==1){

        printf("\nDigite o valor de x para encontrar f(x):");
        scanf("%f",&valorDoX);
    
        if(*x<=valorDoX&&valorDoX<=*(x+pontos-1)){
            printf("\n------RESULTADOS------\n");
            for(i=0;i<pontos;i++){

                contaCima=1.0;
                contaBaixo=1.0;
                for(j=0;j<pontos;j++){

                    if(i!=j){
                       
                        contaCima=contaCima * (valorDoX - *(x + j));
                        contaBaixo=contaBaixo * (*(x + i) - *(x + j));
                        
                        
                    }
               
                }
                
                printf("Ln %i = %.3f\n",c,(contaCima/contaBaixo));
                c++;
                resposta=resposta + ((contaCima / contaBaixo) * *(fx + i));
            }

            printf("\nO ponto %.2f em f(x) e de = %.3f | E a interpolacao e de Grau %i\n",valorDoX,resposta,pontos-1);

            printf("Deseja interpolar outro ponto?(S/N)\n");
            fflush(stdin);
            scanf("%c",&escolha);
            escolha=toupper(escolha);

            if(escolha!='S'){
                verifica=0;
            }

           
        }else{

            printf("\nValor a ser interpolado esta fora do intervalo, por favor digite um valor valido\n");
    

        }
    }
    
    
 

   
    
}
