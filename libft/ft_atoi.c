#include "libft.h"

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
