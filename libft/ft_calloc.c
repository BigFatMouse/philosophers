#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;

	str = malloc(size * count);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (size * count));
	return (str);
}
