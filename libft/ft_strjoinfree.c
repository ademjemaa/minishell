#include "libft.h"

static	int		total(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoinfree(char *s1, char *s2, int crit)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	str = malloc(sizeof(char) * total(s1) + total(s2) + 1);
	if (!str)
		return NULL;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	if (crit == 1)
		free(s1);
	else if (crit == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
	return (str);
}