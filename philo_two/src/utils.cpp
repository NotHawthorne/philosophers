#include "../includes/philo.h"

sem_t	*print_sem;

size_t	philo_strlen(char *str)
{
	for (int i = 0; str && str[i]; i++)
		if (!str[i + 1])
			return ((size_t)i);
	return (0);
}

void	philo_putn(int n)
{
	int	neg;
	int	c;
	int	nc;

	neg = 0;
	nc = '-';
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	if (n >= 10)
		philo_putn(n / 10);
	c = (n % 10) + '0';
	if (neg)
		write(1, &nc, 1);
	write(1, &c, 1);
}

int		philo_printf(const char *fmt, ...)
{
	va_list	vargs;
	char	*str;

	sem_wait(print_sem);
	str = NULL;
	va_start(vargs, (char*)fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if (*(++fmt) == 's')
			{
				str = va_arg(vargs, char*);
				write(1, str, philo_strlen(str));
			}
			else if (*fmt == 'd')
			{
				write(1, "[", 1);
				philo_putn(va_arg(vargs, int));
				write(1, "]", 1);
			}
		}
		else
			write(1, fmt, 1);
		fmt++;
	}
	sem_post(print_sem);
	return (1);
}

int		get_time()
{
	struct timeval	t;
	double			r;
	double			x;
	int				ret;

	gettimeofday(&t, NULL);
	r = (t.tv_sec * 1000) + (t.tv_usec / 1000.0);
	for (x = (double)INT_MAX; r - x > (double)INT_MAX; x += INT_MAX);
	r -= x;
	return ((int)r);
}

int		philo_atoi(char *str)
{
	int	neg;
	int	ret;

	ret = 0;
	neg = 1;
	if (!str || !*str)
		return (0);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
		neg = *str++ == '-' ? -1 : 1;
	while (*str >= '0' && *str <= '9')
		ret = (ret * 10) + (*str++ - '0');
	return (ret * neg);
}
