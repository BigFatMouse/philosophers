#include "philo.h"

// pthread_t  t1, t2;

typedef struct	s_philo
{
	int	philo_num; //mutex left, mutex right, death, 
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	eat_num;
}				t_philo;

typedef struct	s_data
{
	int	philo_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	eat_num;
	t_philo *philo;
}				t_data;

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void    *print(void *str)
{
	for (int i = 0; i < 5; i++)
	//while(1)
	{
		write(1, (char *)str, strlen(str));
		usleep(100000);
	}
	return (NULL);
}

void    *print_num(void *num)
{
	for (int i = 0; i < 2; i++)
	//while(1)
	{
		//printf("fuck you ");
		printf("%d\n", *((int *)num));
		usleep(1000000);
	}
	return (NULL);
}

void	parse_data(t_data *data, int argc, char **argv)
{
	int	i;
	
	i = 1;
	if (argc < 5 || argc > 6)
		ft_error("Error: Enter 4 or 5 argumens");
	while(i < argc)
		if(!ft_isnum(argv[i++]))
			ft_error("Error: Arguments must be positive numbers");
	data->eat_num = 0;
	data->philo_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_num = ft_atoi(argv[5]);
	printf("parce: ");
	printf("%d ", data->philo_num);
	printf("%d ", data->die_time);
	printf("%d ", data->eat_time);
	printf("%d ", data->sleep_time);
	printf("%d\n", data->eat_num);
}

int main(int argc, char **argv)
{
    t_data	data;
	
	char    *str1 = "fuck you\n";
    char    *str2 = "no you\n";
	
	int	i = 0;
	
	
	parse_data(&data, argc, argv); 
	pthread_t  t[data.philo_num];
	int	arr[data.philo_num];
	
	while (i < data.philo_num)
	{
		arr[i] = i;
		i++;
	}
	
	i = 0;
	while(i < data.philo_num)
	{
		if (pthread_create(&t[i], NULL, print_num, (void *)(&arr[i])) == -1)
			ft_error("Error: Can't create thread");
		i++;
	}
	i = 0;
	void *result;
	while(i < data.philo_num)
	{
		if (pthread_join(t[i], &result) == -1)
			ft_error("Error: Can't join thread");
		i++;
	}

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