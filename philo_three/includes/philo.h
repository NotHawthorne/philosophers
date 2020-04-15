#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdarg.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <climits>

extern sem_t	*print_sem;

enum	philo_states
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
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

	int			eat(sem_t *s, int *num);
	int			sleep();
	int			tick();
	int			grabFork(sem_t *s, int *num);
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

	pid_t			*threads;
	Philosopher		**philos;
	sem_t			*forks;
	int				sem_ct;
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
