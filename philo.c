#include "philo.h"

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
			if (g_t(philo->data->time) > philo->last_meal_time
				+ philo->data->die_time)
			{
				pthread_mutex_lock(&philo->eat);
				pthread_mutex_lock(&philo->data->dead);
				printf("%.5zd   %d %sis dead%s\n", g_t(philo->data->time),
					philo->num, RED, RESET);
				philo->data->death = 1;
				pthread_mutex_unlock(&philo->eat);
				return (NULL);
			}
			if (philo->data->meals_num == philo->meals)
				return (NULL);
		}
	}
	return (NULL);
}

void	*philo_life(void *one_philo)
{
	t_philo	*philo;

	philo = (t_philo *)one_philo;
	if ((philo->num) % 2 == 0)
		usleep((philo->data->eat_time) * 1000 + 500);
	while (1)
	{
		pthread_mutex_lock(&philo->left);
		printf("%zd  %d has taken a fork\n", g_t(philo->data->time), philo->num);
		pthread_mutex_lock(philo->right);
		printf("%zd  %d has taken a fork\n", g_t(philo->data->time), philo->num);
		pthread_mutex_lock(&philo->eat);
		philo->last_meal_time = g_t(philo->data->time);
		printf("%zd  %d is eating\n", philo->last_meal_time, philo->num);
		philo->meals++;
		pthread_mutex_unlock(&philo->eat);
		usleep((philo->data->eat_time) * 1000);
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%zd  %d is sleeping\n", g_t(philo->data->time), philo->num);
		usleep((philo->data->sleep_time) * 1000);
		printf("%zd  %d is thinking\n", g_t(philo->data->time), philo->num);
	}
	return (NULL);
}

void	philo_init(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		philo[i].num = i + 1;
		pthread_mutex_init(&philo[i].left, NULL);
		pthread_mutex_init(&philo[i].eat, NULL);
		philo[i].meals = 0;
		philo[i].fead_up = 0;
		philo[i].data = data;
		if (i == data->philos_num - 1)
			philo[i].right = &philo[0].left;
		else
			philo[i].right = &philo[i + 1].left;
		i++;
	}
	pthread_mutex_init(&data->dead, NULL);
	data->death = 0;
	data->time = g_t(0);
}

int	make_threads(t_philo *philo, t_data data,
		pthread_t *philo_thread, pthread_t main_thread)
{
	int	i;

	i = 0;
	while (i < data.philos_num && !data.death)
	{
		if (pthread_create(&philo_thread[i], NULL, philo_life,
				(void *)(&philo[i])) == -1)
			return (ft_error("Can't create thread"));
		i++;
	}
	if (pthread_join(main_thread, NULL) == -1)
		return (ft_error("Can't join thread"));
	i = 0;
	while (i < data.philos_num)
	{
		if (pthread_detach(philo_thread[i]))
			return (ft_error("Can't detach thread"));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*philo_thread;
	pthread_t	main_thread;

	if (parse_data(&data, argc, argv))
		return (1);
	philo_thread = malloc(sizeof(pthread_t) * (data.philos_num));
	if (!philo_thread)
		return (ft_error("Malloc error"));
	philo = malloc(sizeof(t_philo) * (data.philos_num));
	if (!philo)
		return (ft_error("Malloc error"));
	philo_init(philo, &data);
	if (pthread_create(&main_thread, NULL, philo_death, (void *)(philo)) == -1)
		return (ft_error("Can't create thread"));
	if (make_threads(philo, data, philo_thread, main_thread))
		return (1);
	free(philo_thread);
	free(philo);
	write(1, "Exit\n", 5);
	return (0);
}
