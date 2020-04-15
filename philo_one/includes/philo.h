#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdarg.h>
# include <stdio.h>
# include <climits>

enum	philo_states
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
};

class	Fork
{
private:
	bool			in_use;
	pthread_mutex_t	lock;
public:
	Fork();
	~Fork();
	bool			isInUse();
	int				pickUp();
	int				putDown();
};

class	Philosopher
{
private:
	int				health;
	int				state;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				init_time;
	int				last_eat;
	int				num;
	int				eaten;
public:
	Philosopher();
	Philosopher(int ttd, int tte, int tts, int numeat,
						int curtime, int n);
	~Philosopher();

	int			eat(Fork *a, Fork *b);
	int			sleep();
	int			tick();
	int			grabFork(Fork *f);
	int			getHealth();
	int			getEaten();

	int				num_eat;
};

class	Table
{
public:
	Table();
	Table(int num_philos, int ttd, int tte, int tts,
					int numeat, int curtime);
	~Table();

	pthread_t		*threads;
	Philosopher		**philos;
	Fork			*forks;
	int				count;
	bool			dead;
	int				full;
};

typedef struct	s_thread_data
{
	Philosopher	*p;
	Table		*t;
	int			philo_num;
}				t_thread_data;

int		philo_printf(const char *fmt, ...);
size_t	philo_strlen(char *str);
void	philo_putn(int n);
int		philo_atoi(char *str);
int		get_time();

#endif
