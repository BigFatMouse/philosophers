#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned const char	*str1;
	unsigned char		*str2;
	size_t				i;

	if (!src && !dst)
		return (0);
	str1 = src;
	str2 = dst;
	i = -1;
	if (str1 >= str2)
	{
		while (++i < n)
			str2[i] = str1[i];
	}
	else
	{
		while (n > 0)
		{
			n--;
			str2[n] = str1[n];
		}
	}
	return (str2);
}
