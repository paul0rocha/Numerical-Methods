//DANIEL SANTOS SOUZA RA:200387 
//GABRIEL LUCAS PINHEIRO DE ARRUDA RA:200840

#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <math.h>

void sistemalinear(int tipo, float *y, int qtdPontos,float *u0,float *u1,float *u2);
void eliminacao(int tipo,int qtdPontos,float soma_u0,float soma_u0u1,float soma_u0u2,float soma_u1u1,float soma_u1u2,float soma_u2u2,float soma_yu2,float soma_yu1,float soma_yu0);

int main(){

    float *x,*y;
    int qtdPontos, i, j, tipo, verifica = 1;
    char escolha;
    float *u0,*u1,*u2;
    
    
    while (verifica == 1){
        printf("\nDigite o numero de pontos da tabela de x e y: ");
        scanf("%d", &qtdPontos);

        // Alocação para os pontos x e y
        x = (float *)malloc(qtdPontos * sizeof(float));
        y = (float *)malloc(qtdPontos * sizeof(float));

        printf("\nDigite o valor de cada ponto x: \n\n");

        for(i = 0; i < qtdPontos; i++){
            printf("x[%i]: ", i);
            scanf("%f",(x + i));
        }

        printf("\nDigite o valor de cada ponto y: \n\n");

        for(j = 0; j < qtdPontos; j++){
            printf("y[%i]: ", j);
            scanf("%f",(y + j));
        }

        printf("\nDigite o numero correspondente para o tipo de equacao: ");
        printf("\n(1) - Reta");
        printf("\n(2) - Parabola \n\n");
        scanf("%i", &tipo);

        if(tipo == 1){
            // Alocação para os vetores de reta
            u0 = (float *)malloc(qtdPontos * sizeof(float));
            u1 = (float *)malloc(qtdPontos * sizeof(float));
            

            printf("Y = | U0 = | U1 = |\n");

            for(i=0;i<qtdPontos;i++){
                // Construção dos vetores de reta
                u0[i] = pow(x[i],0);
                u1[i] = pow(x[i],1);
                
                printf("%.1f | %.1f  | %.1f  | \n",y[i],u0[i],u1[i]);
            }

            // Chamada da função que constrói o sistema escalar
            sistemalinear(tipo, y, qtdPontos,u0,u1,u2);
            
        } else if(tipo == 2){
            // Alocação para os vetores de uma parábola
            u0 = (float *)malloc(qtdPontos * sizeof(float));
            u1 = (float *)malloc(qtdPontos * sizeof(float));
            u2 = (float *)malloc(qtdPontos * sizeof(float));

            printf("Y = | U0 = | U1 = | U2 = |\n");

            for(i=0;i<qtdPontos;i++){
                // Construção dos vetores de parábola
                u0[i] = pow(x[i],0);
                u1[i] = pow(x[i],1);
                u2[i] = pow(x[i],2);
                
                printf("%.1f | %.1f  | %.1f  | %.1f  | \n",y[i],u0[i],u1[i],u2[i]);
            }

            // Chamada da função que constrói o sistema escalar
            sistemalinear(tipo, y, qtdPontos,u0,u1,u2);
        }

        printf("\nDeseja calcula o mesmo p(x) novamente?(S/N)\n");
        fflush(stdin);
        scanf("%c",&escolha);
        escolha = toupper(escolha);

        if(escolha!='S'){
            verifica = 0;
        }
    }  
}


void sistemalinear(int tipo,float *y, int qtdPontos,float *u0,float *u1,float *u2){
    int i,lin,col;
    float soma_u0=0,soma_u0u1=0,soma_u0u2=0,soma_u1u1=0,soma_u1u2=0,soma_u2u2=0,soma_yu0=0,soma_yu1=0,soma_yu2=0;

    if(tipo==2){
        for(lin=0;lin<qtdPontos;lin++){
            soma_u0+=u0[lin]*u0[lin];
            soma_u0u1+=u0[lin]*u1[lin];
            soma_u0u2+=u0[lin]*u2[lin];
            soma_u1u1+=u1[lin]*u1[lin];
            soma_u1u2+=u1[lin]*u2[lin];
            soma_u2u2+=u2[lin]*u2[lin];
            soma_yu0+=y[lin]*u0[lin];
            soma_yu1+=y[lin]*u1[lin];
            soma_yu2+=y[lin]*u2[lin];
        }

        printf("-------------------SISTEMA--LINEAR-------------------\n");
        for(lin=0;lin<qtdPontos;lin++){

            for(col=0;col<4;col++){
                if(lin==0&&col==0){
                    printf(" %.1f  |",soma_u0);
                }
                else if (lin==0&&col==1||lin==1&&col==0)
                {
                    printf(" %.1f  |",soma_u0u1);
                }else if (lin==0&&col==2||lin==2&&col==0)
                {
                    printf(" %.1f  |",soma_u0u2);
                }else if (lin==1&&col==1)
                {
                    printf(" %.1f  |",soma_u1u1);
                }else if (lin==1&&col==2||lin==2&&col==1)
                {
                    printf(" %.1f  |",soma_u1u2);
                }else if (lin==2&&col==2)
                {
                    printf(" %.1f  |",soma_u2u2);
                }else if (lin==0&&col==3)
                {
                    printf(" %.1f  |",soma_yu0);
                }else if (lin==1&&col==3)
                {
                    printf(" %.1f  |",soma_yu1);
                }else if (lin==2&&col==3)
                {
                    printf(" %.1f  |",soma_yu2);
                }
            } 
            printf("\n");
        }  

        // Chamada da função que faz o método de gauss de uma parábola
         eliminacao(tipo,qtdPontos,soma_u0,soma_u0u1,soma_u0u2,soma_u1u1,soma_u1u2,soma_u2u2,soma_yu2,soma_yu1,soma_yu0);
    }else{
         for(lin=0;lin<qtdPontos;lin++){

            soma_u0+=u0[lin]*u0[lin];
            soma_u0u1+=u0[lin]*u1[lin];
            soma_u1u1+=u1[lin]*u1[lin];
            soma_yu0+=y[lin]*u0[lin];
            soma_yu1+=y[lin]*u1[lin];

        }

        printf("-------------------SISTEMA--LINEAR-------------------\n");
        for(lin=0;lin<qtdPontos;lin++){

            for(col=0;col<4;col++){
                if(lin==0&&col==0){
                    printf(" %.1f  |",soma_u0);
                }
                else if (lin==0&&col==1||lin==1&&col==0)
                {
                    printf(" %.1f  |",soma_u0u1);
                }else if (lin==1&&col==1)
                {
                    printf(" %.1f  |",soma_u1u1);
                }else if (lin==0&&col==3)
                {
                    printf(" %.1f  |",soma_yu0);
                }else if (lin==1&&col==3)
                {
                    printf(" %.1f  |",soma_yu1);
                }
            } 
            printf("\n");
        }
        // Chamada da função que faz o método de gauss de uma reta
        eliminacao(tipo,qtdPontos,soma_u0,soma_u0u1,soma_u0u2,soma_u1u1,soma_u1u2,soma_u2u2,soma_yu2,soma_yu1,soma_yu0);
    }
}

void eliminacao(int tipo,int qtdPontos,float soma_u0,float soma_u0u1,float soma_u0u2,float soma_u1u1,float soma_u1u2,float soma_u2u2,float soma_yu2,float soma_yu1,float soma_yu0){

    float pivo,M,M2,aux,aux2,aux3,conta,conta1,resultado,auxl1[4],auxl2[4];
    int lin, col;

    if(tipo==1){
        pivo=soma_u0;
        M=(soma_u0u1/pivo);
        aux=(soma_u0u1-(pivo*M));
        aux2=(soma_u1u1-(soma_u0u1*M));
        aux3=(soma_yu1-(soma_yu0*M));


        if(aux==0){

            conta=(aux3/aux2);
            resultado=((soma_yu0-(soma_u0u1*conta))/pivo);

            printf("-------------------ELIMINACAO DE GAUSS-------------------\n");

            for(lin=0;lin<qtdPontos;lin++){

                for(col=0;col<4;col++){
                    if(lin==0&&col==0){
                        printf(" %.1f  |",soma_u0);
                    }else if (lin==0&&col==1)
                    {
                        printf(" %.1f  |",soma_u0u1);
                    }else if (lin==0&&col==2)
                    {
                        printf(" %.1f  |",soma_yu0);
                    }else if (lin==1&&col==0)
                    {
                        printf(" %.1f  |",aux);
                    }else if (lin==1&&col==1)
                    {
                        printf(" %.1f  |",aux2);
                    }else if (lin==1&&col==2)
                    {
                        printf(" %.1f  |",aux3);
                    }
                }

                printf("\n");
            }
        }
        
        printf("\nP(X)= %.1f + %.1f x",resultado,conta);
    }else{
        pivo=soma_u0;
        M=(soma_u0u1/pivo);
        M2=(soma_u0u2/pivo);

        //linha 1
        auxl1[0]=(soma_u0u1-(pivo*M));
        auxl1[1]=(soma_u1u1-(soma_u0u1*M));
        auxl1[2]=(soma_u1u2-(soma_u0u2*M));
        auxl1[3]=(soma_yu1-(soma_yu0*M));

        //linha2
        auxl2[0]=(soma_u0u2-(pivo*M2));
        auxl2[1]=(soma_u1u2-(soma_u0u1*M2));
        auxl2[2]=(soma_u2u2-(soma_u0u2*M2));
        auxl2[3]=(soma_yu2-(soma_yu0*M2));

        if(auxl2[1]!=0){

            pivo=auxl1[1];
            M2=(auxl2[1]/pivo);

            auxl2[1]=(auxl2[1]-(auxl1[1]*M2));
            auxl2[2]=(auxl2[2]-(auxl1[2]*M2));
            auxl2[3]=(auxl2[3]-(auxl1[3]*M2));

            printf("-------------------ELIMINACAO DE GAUSS-------------------\n");

            for(lin=0;lin<qtdPontos;lin++){

                for(col=0;col<4;col++){
                    if(lin==0&&col==0){
                        printf(" %.1f  |",soma_u0);
                    }else if (lin==0&&col==1)
                    {
                        printf(" %.1f  |",soma_u0u1);
                    }else if (lin==0&&col==2)
                    {
                        printf(" %.1f  |",soma_u0u2);
                    }else if (lin==0&&col==3)
                    {
                        printf(" %.1f  |",soma_yu0);
                    }else if (lin==1&&col==0)
                    {
                        printf(" %.1f  |",auxl1[0]);
                    }else if (lin==1&&col==1)
                    {
                        printf(" %.1f  |",auxl1[1]);
                    }else if (lin==1&&col==2)
                    {
                        printf(" %.1f  |",auxl1[2]);
                    }else if (lin==1&&col==3)
                    {
                        printf(" %.1f  |",auxl1[3]);
                    }else if (lin==2&&col==0)
                    {
                        printf(" %.1f  |",auxl2[0]);
                    }else if (lin==2&&col==1)
                    {
                        printf(" %.1f  |",auxl2[1]);
                    }else if (lin==2&&col==2)
                    {
                        printf(" %.1f  |",auxl2[2]);
                    }else if (lin==2&&col==3)
                    {
                        printf(" %.1f  |",auxl2[3]);
                    }
                } 
                printf("\n");
            }
        }
        conta=auxl2[3]/auxl2[2];
        conta1=(-(auxl1[2]*conta)+auxl1[3])/auxl1[1];
        resultado=(-(soma_u0u1*conta1)-(soma_u0u2*conta)+soma_yu0)/soma_u0;

        printf("\nP(X)= %.1f + %.1f x + %.1f x^2",resultado,conta1,conta);
    }
}
