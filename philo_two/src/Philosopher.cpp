#include "../includes/philo.h"

Philosopher::Philosopher()
{
	health = 100;
	state = THINKING;
	time_die = 0;
	time_eat = 0;
	time_sleep = 0;
	num_eat = 0;
	init_time = 0;
	num = 0;
}

Philosopher::Philosopher(int ttd, int tte, int tts, int numeat, int curtime, int n)
{
	health = ttd;
	state = THINKING;
	time_die = ttd;
	time_eat = tte;
	time_sleep = tts;
	num_eat = numeat;
	init_time = curtime;
	last_eat = curtime;
	num = n;
	eaten = 0;
	philo_printf("philo %d spawned!\n", n);
}

int		Philosopher::sleep()
{
	double	t;
	double	tod;

	state = SLEEPING;
	t = get_time();
	philo_printf("%d %d is sleeping\n", (int)t, num);
	while ((tod = get_time()) - t < time_sleep && state != DEAD)
		tick();
	return (1);
}

int		Philosopher::tick()
{
	health = time_die - (get_time() - last_eat);
	if (health <= 0)
	{
		state = DEAD;
		philo_printf("%d %d died\n", get_time(), num);
	}
	usleep(3);
	return (1);
}

int		Philosopher::grabFork(sem_t *s, int *num)
{
	int	t;

	while (*num < 2 && state != DEAD)
		tick();
	if (state == DEAD)
		return (-1);
	sem_wait(s);
	*num--;
	t = get_time();
	philo_printf("%d %d has taken a fork\n", t, this->num);
	return (1);
}

int		Philosopher::eat(sem_t *s, int *num)
{
	int	tod;

	if (state == DEAD)
		return (-1);
	philo_printf("%d %d is thinking\n", get_time(), this->num);
	state = THINKING;
	grabFork(s, num);
	grabFork(s, num);
	philo_printf("%d %d is eating\n", get_time(), this->num);
	tod = get_time();
	state = EATING;
	while (get_time() - tod < time_eat && state != DEAD)
		tick();
	if (state == DEAD)
		return (-1);
	health = time_die;
	last_eat = get_time();
	sem_post(s);
	*num++;
	sem_post(s);
	*num++;
	eaten++;
	return (1);
}

Philosopher::~Philosopher() { }
int		Philosopher::getHealth() { return (health); }
int		Philosopher::getEaten() { return (eaten); }
