#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define RESET   "\033[0m"
#define RED     "\033[1;31m"

typedef struct	s_data
{
	int				philos_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	int				death;
	ssize_t			time;
	pthread_mutex_t	dead;
}					t_data;

typedef struct		s_philo
{
	int				num; //mutex left, mutex right, death, 
	ssize_t			last_meal_time;
	t_data			*data;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	pthread_mutex_t	eat;
}					t_philo;

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_isnum(const char *str);
int		ft_error(char *str);
int		parse_data(t_data *data, int argc, char **argv);
#endif