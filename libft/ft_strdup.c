#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}
