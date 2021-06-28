#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (n != 0)
	{
		i = 0;
		str = s;
		while (i < n)
		{
			str[i] = '\0';
			i++;
		}
	}
}
