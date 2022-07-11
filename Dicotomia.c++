#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct conta{
   float coenf;
   float expoe;
   int tam;
}conta;

typedef struct intervalo{
    float a;
    float b;
    float m;
}intervalo;


void aloca(conta**p, int tam);
float calculafunc(conta *p, float x);
void verifica(conta *p, intervalo *i);
void alocaInter(intervalo **p);

int main(){
    conta *cont;
    intervalo *inter;
    float precisao,continha,media,resultM,resultA,resultB,contaK;
    int i,c,termos;

    printf("Digite a quantidade de termos: ");
    scanf("%i",&termos);

    alocaInter(&inter);
   
    aloca(&cont,termos);
    cont->tam=termos;

    for(i=0,c=1;termos>i;i++,c++){
        
        printf("Digite o valor do %i coeficiente e o valor do expoente: ",c);
        scanf("%f %f",&(cont+i)->coenf,&(cont+i)->expoe);

    }

    printf("Digite o intervalo (valores entre virgula por favor): ");
    scanf("%f,%f", &inter->a, &inter->b);
    
    printf("Digite o valor da precisao (utilize '.' para casa decimal): ");
    scanf("%f",&precisao);
    inter->m=(inter->a+inter->b)/2;

    int iv=0;


    contaK=(log(inter->b-inter->a)-log(precisao))/log(2);


    while (fabs(calculafunc(cont,inter->m))>precisao){    
        printf("\nI=%i, A=%.3f, M=%.3f, B=%.3f | f(a)=%.3f, f(m)=%.3f, f(b)=%.3f\n", iv, inter->a,inter->m,inter->b,calculafunc(cont,inter->a),calculafunc(cont,inter->m),calculafunc(cont,inter->b));
        verifica(cont,inter);
        iv++;
    }
    
    printf("\nI=%i, A=%.3f, M=%.3f, B=%.3f | f(a)=%.3f, f(m)=%.3f, f(b)=%.3f\n", iv, inter->a,inter->m,inter->b,calculafunc(cont,inter->a),calculafunc(cont,inter->m),calculafunc(cont,inter->b));
    printf("\nResultado da Raiz e de : %.3f | e o erro e de : %.3f | o valor de K= %.3f",inter->m, calculafunc(cont,inter->m),contaK);

    return(0);
}

    //ALOCAÇÃO DA CONTA
void aloca(conta **p, int tam)
{
	if((*p = (conta *)malloc( tam*sizeof(conta)))==NULL){
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
	
}

    //ALOCAÇÃO DO INTERVALO DE A,B E M
void alocaInter(intervalo **p)
{
	if((*p = (intervalo *)malloc(sizeof(intervalo)))==NULL){
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
	
}		

    //FUNÇÃO QUE SUBSTITUI E CALCULA A F(X)
float calculafunc(conta *p,float x){
    int i;
    float resultado=0;

    for(i=0;p->tam>i;i++){
        
        resultado=resultado+(p+i)->coenf*pow(x,(p+i)->expoe);

    }
    return(resultado);
}

     //FUNÇÃO DO CODIGO QUE VERIFICA O VALOR DE M E SUBSTITUI EM A OU B DE ACORDO COM A EXIGENCIA
void verifica(conta *p, intervalo *i){

    if(calculafunc(p,i->a)<0 && calculafunc(p,i->m)<0){
        i->a=i->m;
        i->m=(i->a+i->b)/2;

    }else if(calculafunc(p,i->b)<0 && calculafunc(p,i->m)<0){
        i->b=i->m;
        i->m=(i->a+i->b)/2;

    }else if(calculafunc(p,i->a)>0 && calculafunc(p,i->m)>0){
        i->a=i->m;
        i->m=(i->a+i->b)/2;

    }else if(calculafunc(p,i->b)>0 && calculafunc(p,i->m)>0){
        i->b=i->m;
        i->m=(i->a+i->b)/2;

    }else{
        printf("Nao existe raiz do problema");
    }

}
