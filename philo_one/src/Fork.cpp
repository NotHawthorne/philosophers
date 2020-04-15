#include "../includes/philo.h"

Fork::Fork()
{
	in_use = false;
	pthread_mutex_init(&lock, NULL);
}

Fork::~Fork()
{
	pthread_mutex_destroy(&lock);
}

int		Fork::pickUp()
{
	if (!in_use)
	{
		pthread_mutex_lock(&lock);
		in_use = true;
		return (1);
	}
	return (0);
}

int		Fork::putDown()
{
	if (in_use)
	{
		pthread_mutex_unlock(&lock);
		in_use = false;
	}
	return (1);
}

bool	Fork::isInUse() { return (in_use); }
