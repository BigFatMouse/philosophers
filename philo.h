#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define RESET   "\033[0m"
# define RED     "\033[1;31m"

typedef struct s_data
{
	int				philos_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	int				death;
	int				fead_up;
	ssize_t			time;
	pthread_mutex_t	dead;
}					t_data;

typedef struct s_philo
{
	int				num;
	ssize_t			last_meal_time;
	int				meals;
	int				fead_up;
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
ssize_t	g_t(ssize_t time);
int		check_eat_time(t_philo *philo);
void	count_eat_time(t_philo *philo);
void	*philo_death(void *one_philo);
void	*philo_life(void *one_philo);
void	ft_usleep(unsigned int n);

#endif