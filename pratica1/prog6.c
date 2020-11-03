/* Baseado na Figura 2.10 do livro texto, evitando warnings do código original. */ 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 //Numero de threads

void* f_thread(void *v) {

	//Recebe o identificador da thread
	int t_id = *(int*) v;
	//Imprime o identificador da thread
	printf("Thread %d executou.\n", t_id);  
  	return NULL;  
  	
}

int main() {

 	//Vetor de threads
	pthread_t threads[N];
	//Contador
	int i, id[N];
	
	//Criacao dos threads
	for (i =0; i < N; i++) {
		id[i] = i;
		pthread_create(&threads[i], NULL, f_thread, (void *) &id[i]);
	}
	
	//Aguardar os threads terminarem antes de prosseguir
	 for (i = 0; i < N; i++) {
	    pthread_join(threads[i], NULL); 
	}
	
	printf("Threads terminaram. Fim do programa. \n");
}
