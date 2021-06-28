#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_isnum(const char *str);

#endif