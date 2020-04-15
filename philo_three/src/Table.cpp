#include "../includes/philo.h"

Table::Table() { };

Table::Table(int num_philos, int ttd, int tte, int tts, int numeat, int curtime)
{
	philos = new Philosopher*[num_philos];
	count = num_philos;
	threads = new pid_t[num_philos];

	sem_unlink("/philoSem");
	forks = sem_open("/philoSem", O_CREAT, 0644, num_philos);
	for (int i = 0; i != num_philos; i++)
		philos[i] = new Philosopher(ttd, tte, tts, numeat, curtime, i + 1);
	count = num_philos;
	sem_ct = num_philos;
	dead = false;
	full = 0;
}

Table::~Table()
{
	sem_close(forks);
	sem_close(print_sem);
	sem_unlink("/philoSem");
	sem_unlink("/printSem");
	for (int i = 0; i != count; i++)
		delete philos[i];
	delete[] philos;
	delete[] threads;
};
