#include <stdio.h>
#include <pthread.h>

// rotina que recebe id como parâmetro e imprime na tela
static void	*routine(void *thread_id)
{
	long	taskid;

	taskid = (long)thread_id;
	printf("hello world from thread #%ld\n", taskid);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[5];
	long	taskid[5];

	// criar threads
	for (int i = 0; i < 5; i++)
	{
		taskid[i] = i;
		if (pthread_create(&threads[i], NULL, &routine, (void *)taskid[i]) != 0)
		{
			printf("Erro ao criar thread\n");
			return (1);
		}
	}

	// unir threads
	for (int i = 0; i < 5; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Erro ao unir thread\n");
			return (1);
		}
	}

	pthread_exit(NULL);
	return (0);
}