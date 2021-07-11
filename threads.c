#include "philo.h"

int	check_eat_time(t_philo *philo)
{
	if (philo->data->meals_num > 0)
	{
		if (philo->data->fead_up == philo->data->philos_num)
		{
			pthread_mutex_lock(&philo->data->write);
			return (1);
		}
	}
	return (0);
}

void	count_eat_time(t_philo *philo)
{
	if (philo->data->meals_num == philo->meals)
		philo->data->fead_up++;
}

void	ft_usleep(unsigned int n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
				((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

void	*philo_life(void *one_philo)
{
	t_philo	*philo;

	philo = (t_philo *)one_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->left);
		printf("%lu  %d has taken a fork\n", g_t(philo->data->time), philo->num);
		pthread_mutex_lock(philo->right);
		printf("%lu  %d has taken a fork\n", g_t(philo->data->time), philo->num);
		pthread_mutex_lock(&philo->eat);
		philo->last_meal_time = g_t(philo->data->time);
		pthread_mutex_unlock(&philo->eat);
		printf("%lu  %d is eating\n", g_t(philo->data->time), philo->num);
		philo->meals++;
		count_eat_time(philo);
		ft_usleep((philo->data->eat_time) * 1000);
		check_eat_time(philo);
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%lu  %d is sleeping\n", g_t(philo->data->time), philo->num);
		ft_usleep((philo->data->sleep_time) * 1000);
		printf("%lu  %d is thinking\n", g_t(philo->data->time), philo->num);
	}
	return (NULL);
}

void	*philo_death(void *one_philo)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)one_philo;
	while (1)
	{	
		i = -1;
		while (++i < philo->data->philos_num)
		{
			if (g_t((&philo[i])->data->time) > (&philo[i])->last_meal_time
				+ (&philo[i])->data->die_time)
			{
				pthread_mutex_lock(&(&philo[i])->eat);
				pthread_mutex_lock(&(&philo[i])->data->dead);
				printf("%lu %d %sis dead%s\n", g_t((&philo[i])->data->time),
					(&philo[i])->num, RED, RESET);
				philo->data->death = 1;
				pthread_mutex_unlock(&(&philo[i])->eat);
				return (NULL);
			}
		}
		if (check_eat_time(philo))
			return (NULL);
	}
	return (NULL);
}
