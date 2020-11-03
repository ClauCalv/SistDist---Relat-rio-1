#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Variável compartilhada
volatile int s = 0; 


void* f_thread_0(void *v) {

	//Thread 0 atribui o valor de s como 0	
  	s = 0;
  	
	//Libera a execução para outro thread. Alternativa: sleep();
	pthread_yield();
	
	//Imprime o valor de s
  	printf("Thread 0, s = %d.\n", s);
  	 
  	return NULL;
}

void* f_thread_1(void *v) {

	//Thread 1 atribui o valor de s como 1
	s = 1;
	
	//Libera a execução para outro thread. Alternativa: sleep();
	pthread_yield();
	
	//Imprime o valor de s
  	printf("Thread 1, s = %d.\n", s); 
  	return NULL;
}

int main() {

	//Declaração de 2 threads
  	pthread_t thr0, thr1;
	
	//Cria 2 threads que operam sobre uma variável compartilhada
  	pthread_create(&thr0, NULL, f_thread_0, NULL);
  	pthread_create(&thr1, NULL, f_thread_1, NULL);

	//Aguarda pelo resultado dos threads
	pthread_join(thr0, NULL); 
	pthread_join(thr1, NULL);
  	
  	return 0;
}

