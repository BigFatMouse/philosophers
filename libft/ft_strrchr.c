#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + n);
	while (n >= 0)
	{
		if (s[n] == c)
			return ((char *)s + n);
		n--;
	}
	return (NULL);
}
