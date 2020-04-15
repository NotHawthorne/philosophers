#include "../includes/philo.h"

void	*manage_philo(void *ptr)
{
	t_thread_data	*d = (t_thread_data*)ptr;
	while (d->p->getHealth() > 0 && d->t->dead == false)
	{
		d->p->eat(&d->t->forks[d->philo_num], &d->t->forks[(d->philo_num + 1) % d->t->count]);
		if (d->p->num_eat >= 0 && d->p->getEaten() >= d->p->num_eat)
		{
			philo_printf("%d %d is full\n", get_time(), d->philo_num);
			d->t->full++;
			pthread_exit(NULL);
		}
		d->p->sleep();
	}
	philo_printf("%d %d died\n", get_time(), d->philo_num);
	d->t->dead = true;
	return (NULL);
}

int		main(int argc, char **argv)
{
	int		num;
	int		ttd;
	int		tte;
	int		tts;
	int		numeat;
	double	curtime;
	Table	*t;
	t_thread_data	*thread_data;

	if (argc < 5)
		return (philo_printf("usage: ./philo_one (number of philosophers) (time_to_die) (time_to_eat) (time_to_sleep) [number of times each philosopher must eat]\n"));
	num = philo_atoi(argv[1]);
	ttd = philo_atoi(argv[2]);
	tte = philo_atoi(argv[3]);
	tts = philo_atoi(argv[4]);
	numeat = argc >= 6 ? philo_atoi(argv[5]) : -1;
	curtime = get_time();
	t = new Table(num, ttd, tte, tts, numeat, curtime);
	thread_data = new t_thread_data[num];
	for (int i = 0; i != num; i++)
	{
		thread_data[i].p = t->philos[i];
		thread_data[i].t = t;
		thread_data[i].philo_num = i + 1;
		pthread_create(&t->threads[i], NULL, &manage_philo, (void*)&thread_data[i]);
	}
	while (t->dead == false)
		if (numeat >= 0 && t->full == num)
			break ;
	delete t;
	delete[] thread_data;
	return (1);
}
