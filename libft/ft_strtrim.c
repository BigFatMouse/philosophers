#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len && (ft_strchr(set, s1[len])))
		len--;
	if (len > 0)
		str = ft_substr(s1, i, len - i + 1);
	else
		str = ft_substr(s1, i, 1);
	return (str);
}
