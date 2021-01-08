/*
O programa utiliza 4 threads para imprimir 4 mensagens, uma por thread. As threads 'A' e 'B' devem imprimir suas mensagens antes das threads 'C' e 'D' imprimirem suas mensagens.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  4

/* Variaveis globais */
int count = 0; //contador de quantas threads ja imprimiram alguma mensagem
pthread_mutex_t count_mutex;
pthread_cond_t count_cond;

/* imprime 'tudo bem?' */
void* A(void* t)
{
	pthread_mutex_lock(&count_mutex);
	
	puts("tudo bem?");
	count++;
	if(count == 2) //liberar a execucao de todas as threads se 'A' e 'B' ja imprimiram suas msgs
		pthread_cond_broadcast(&count_cond);
		
	pthread_mutex_unlock(&count_mutex);

	pthread_exit(NULL);
}

/* imprime 'bom dia!' */
void* B(void* t)
{
	pthread_mutex_lock(&count_mutex);
	
	puts("bom dia!");
	count++;
	if(count == 2) //liberar a execucao de todas as threads se 'A' e 'B' ja imprimiram suas msgs
		pthread_cond_broadcast(&count_cond);
		
	pthread_mutex_unlock(&count_mutex);

	pthread_exit(NULL);
}

/* imprime 'ate mais!' */
void* C(void* t)
{
	pthread_mutex_lock(&count_mutex);
	
	while(count < 2) //a thread espera ate que as threads 'A' e 'B' tenham imprimido suas msgs
		pthread_cond_wait(&count_cond, &count_mutex);

	puts("ate mais!");
	count++;
	pthread_mutex_unlock(&count_mutex);

	pthread_exit(NULL);
}

/* imprime 'boa tarde!' */
void* D(void* t)
{
	pthread_mutex_lock(&count_mutex);

	while(count < 2) //a thread espera ate que as threads 'A' e 'B' tenham imprimido suas msgs
		pthread_cond_wait(&count_cond, &count_mutex);

	puts("boa tarde!");
	count++;
	pthread_mutex_unlock(&count_mutex);

	pthread_exit(NULL);
}


/* Funcao principal */
int main(int argc, char* argv[])
{
	pthread_t threads[NTHREADS];

	/* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init(&count_cond, NULL);

	/* Cria as threads */
	pthread_create(&threads[0], NULL, A, NULL);
	pthread_create(&threads[1], NULL, B, NULL);
	pthread_create(&threads[2], NULL, C, NULL);
	pthread_create(&threads[3], NULL, D, NULL);

	/* Espera todas as threads completarem */
	for(int i = 0; i < NTHREADS; i++)
	{
    	pthread_join(threads[i], NULL);
	}
	printf("FIM.\n");

	/* Desaloca variaveis e termina */
	pthread_mutex_destroy(&count_mutex);
	pthread_cond_destroy(&count_cond);
	
	return 0;
}
