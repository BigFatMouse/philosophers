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
	printf("parce: ");
	printf("%d ", data->philos_num);
	printf("%d ", data->die_time);
	printf("%d ", data->eat_time);
	printf("%d ", data->sleep_time);
	printf("%d\n", data->meals_num);
	return (0);
}

int	ft_error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}

ssize_t	g_t(ssize_t time)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - time);
}

int	ft_isnum(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	num;

	i = 0;
	minus = 0;
	num = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		minus = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (minus == 1)
		num = -num;
	return (num);
}
