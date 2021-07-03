#include "philo.h"

int	parse_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error("Error: Enter 4 or 5 argumens"));
	while (++i < argc)
		if (!ft_isnum(argv[i]) || !ft_atoi(argv[i]))
			return (ft_error("Error: All arguments must be positive numbers"));
	data->meals_num = 0;
	data->philos_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_num = ft_atoi(argv[5]);
	return (0);
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

void	print_res(t_data data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data.philos_num)
	{
		printf("%d has eaten %d times\n", i + 1, philo[i].meals);
		i++;
	}
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
	return (0);
}
