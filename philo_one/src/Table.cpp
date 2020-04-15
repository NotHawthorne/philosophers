#include "../includes/philo.h"

Table::Table() { };

Table::Table(int num_philos, int ttd, int tte, int tts, int numeat, int curtime)
{
	philos = new Philosopher*[num_philos];
	count = num_philos;
	forks = new Fork[num_philos];
	threads = new pthread_t[num_philos];

	for (int i = 0; i != num_philos; i++)
		philos[i] = new Philosopher(ttd, tte, tts, numeat, curtime, i + 1);
	count = num_philos;
	dead = false;
	full = 0;
}

Table::~Table()
{
	for (int i = 0; i != count; i++)
		delete philos[i];
	delete[] philos;
	delete[] forks;
	delete[] threads;
};
