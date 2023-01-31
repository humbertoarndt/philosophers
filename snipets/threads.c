#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t	mutex;


void	*routine()
{
	// race condition - quando as thread acessam e alteram a mesmoa posição de memória
		// ler mails
		// incrementar valor
		// escrever mails na mmeória
	// printf("[create_threads]\tThread |%ld| criada\n", pthread_self());
	for (int i =0; i < 1000; i++)
	{
		// travar thread
		pthread_mutex_lock(&mutex);

		// incrementar variável
		mails++;

		// destravar thread
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int argc, char *argv[])
{
	int	i;
	pthread_t	th[8];

	// iniciar mutex
	pthread_mutex_init(&mutex, NULL);

	// iniciar threads
	for (i = 0; i < 8; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			perror("Falha ao criar thread.");
			return (1);
		}
		printf("Thread |%d| iniciada\n", i);
	}

	// finalizar threads
	for (i = 0; i < 8; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Falha ao unir thread.");
			return (1);
		}
		printf("Thread |%d| finalizada\n", i);
	}

	// destruir mutex
	pthread_mutex_destroy(&mutex);
	printf("Number of mails |%d|\n", mails);

	return (0);
}
