#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* define pid_t */
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h> /* fork() */
#define TAM_MAX 20


int primo(int inteiro){
	int i,d;
	for(i=2; i<inteiro; i++){
		if(inteiro%i==0){
			d++;
		}
	}	
	if(d!=0 || inteiro <=1){
		return 0;
	}
	return 1;
}

int main() {

	int *valores, *p;//p[0]= numero de primos; p[1]= numero de processos no instante; p[2]= contagem de processos restantes
	int ndv=0, inteiro, i, e; //numero de valores
	int protection = PROT_READ | PROT_WRITE;
  	int visibility = MAP_SHARED | MAP_ANON;
	char valor;
	pid_t filho;
		
		
	valores= (int*) malloc(TAM_MAX*sizeof(int));
  	p = (int*) mmap(NULL, 3*sizeof(int), protection, visibility, 0, 0);
	p[0]=0;p[1]=0;p[2]=0;
	
	while(valor!='\n'){
		scanf("%d%c", &valores[ndv], &valor);
		ndv++;
	}
	
//criando os processos paralelos (se for um filho sai, se for pai continua contando e criando processos)	
	for(i=0; i<ndv; i++){
		p[2]++;
		filho=fork();
		if (filho==0){
		//se quatro processos ocorrendo, espera algum outro filho terminar
			while(p[1]>=4){
				sleep(1);
			}
			inteiro=valores[i];
			p[1]++;
			break;
		}
	}		
	
// processos pai e filho
	
	if(filho==0){
		e=primo(inteiro);
		if(e==1){
			p[0]++;
		}	
	}
	else{
		while(p[2]!=0){
			sleep(1);
		}
		printf("%d\n", p[0]);
	}
// liberando memoria	
	free(valores);
	p[1]--;	//avisa que o processo chegou ao fim	
 	p[2]--; 
  return 0;
}
