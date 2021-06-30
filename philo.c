#include "philo.h"

// pthread_t  t1, t2;

int	ft_error(char *str)
{
	printf("Error: %s\n", str);
	return(1);
}

ssize_t	get_time(ssize_t time)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - time);
}

void	*philo_death(void *one_philo)
{
	int		i;
	int		limit;
	t_philo	*philo;
	
	philo = (t_philo *)one_philo;
	int j = 0;
	while (1)
	{	
		i = 0;
		while (i < philo->data->philos_num)
		{
			limit = philo->last_meal_time + philo->data->die_time;
			if (get_time(philo->data->time) > limit)
			{
				pthread_mutex_lock(&philo->eat);
				pthread_mutex_lock(&philo->data->dead);
				printf("%.5zd   %d %sis dead%s\n", get_time(philo->data->time), philo->num, RED, RESET);
				philo->data->death = 1;
				pthread_mutex_unlock(&philo->eat);
				return (NULL);
			}
			//if return (NULL);
			
			i++;
		}
		//j++;
	}
	return (NULL);
}

void    *philo_life(void *one_philo)
{
	t_philo	*philo;
	
	philo = (t_philo *)one_philo;
	
	if ((philo->num) % 2 == 0)
		usleep((philo->data->eat_time) * 1000 + 500);
	while (1) //  пока все не поедят ??
	{
		pthread_mutex_lock(&philo->left);
		printf("%.5zd   %d has taken left fork\n", get_time(philo->data->time), philo->num);
		pthread_mutex_lock(philo->right);
		printf("%.5zd   %d has taken right fork\n", get_time(philo->data->time), philo->num);
		pthread_mutex_lock(&philo->eat);
		philo->last_meal_time = get_time(philo->data->time);
		printf("%.5zd   %d is eating\n", philo->last_meal_time, philo->num);
		pthread_mutex_unlock(&philo->eat);
		usleep((philo->data->eat_time) * 1000);
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%.5zd   %d is sleeping\n", get_time(philo->data->time), philo->num);
		usleep((philo->data->sleep_time) * 1000);
		printf("%.5zd   %d is thinking\n", get_time(philo->data->time), philo->num);
	}
	return (NULL);
}

int	parse_data(t_data *data, int argc, char **argv)
{
	int	i;
	
	i = 0;
	if (argc < 5 || argc > 6)
		return(ft_error("Error: Enter 4 or 5 argumens"));
	while(++i < argc)
		if(!ft_isnum(argv[i]) || !ft_atoi(argv[i]))
			return(ft_error("Error: All arguments must be positive numbers"));
	data->eat_num = 0;
	data->philos_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_num = ft_atoi(argv[5]);
	printf("parce: ");
	printf("%d ", data->philos_num);
	printf("%d ", data->die_time);
	printf("%d ", data->eat_time);
	printf("%d ", data->sleep_time);
	printf("%d\n", data->eat_num);
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
		philo[i].data = data;
		if (i == data->philos_num - 1)
			philo[i].right = &philo[0].left;
		else
			philo[i].right = &philo[i + 1].left;
		i++;
	}
	pthread_mutex_init(&data->dead, NULL);
	data->death = 0;
	data->time = get_time(0);
}

int main(int argc, char **argv)
{
    t_data		data;
	t_philo		*philo;
	pthread_t	*philo_thread;
	pthread_t	main_thread;
	
	int	i = 0;
	
	if (parse_data(&data, argc, argv))
		return (1);
	philo_thread = malloc(sizeof(pthread_t) * (data.philos_num + 1));
	if (!philo_thread)
		return(ft_error("Malloc error"));
	philo = malloc(sizeof(t_philo) * (data.philos_num + 1));
	if (!philo)
		return(ft_error("Malloc error"));
	philo_init(philo, &data);
	
	if (pthread_create(&main_thread, NULL, philo_death, (void *)(&philo[i])) == -1)
			return(ft_error("Can't create thread"));
		
	i = 0;
	while (i < data.philos_num && !data.death)
	{
		if (pthread_create(&philo_thread[i], NULL, philo_life, (void *)(&philo[i])) == -1)
			ft_error("Can't create thread");
		i++;
	}
	i = 0;
	if (pthread_join(main_thread, NULL) == -1)
			return(ft_error("Can't join thread"));
	
	while (i < data.philos_num)
	{
		pthread_detach(philo_thread[i]);
		i++;
	}
	free(philo_thread);
	free(philo);

    // if (pthread_create(&t1, NULL, print, (void *)str1) == -1)
	// 	ft_error("Error: Can't create thread");
    // if (pthread_create(&t2, NULL, print, (void *)str2) == -1)
	// 	ft_error("Error: Can't create thread");
	//usleep(3000000);
	

	// void *result;
	// if (pthread_join(t1, &result) == -1)
	// 	ft_error("Error: Can't join thread");
	// if (pthread_join(t2, &result) == -1)
	// 	ft_error("Error: Can't join thread");
	
	write(1, "Exit\n", 5);
    return (0);
}