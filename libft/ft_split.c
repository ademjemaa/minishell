/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:56:31 by abarbour          #+#    #+#             */
/*   Updated: 2020/05/28 18:57:40 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbr_word(char const *str, char sep)
{
	size_t i;
	size_t nb;

	i = 0;
	nb = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) != sep)
		{
			while ((*(str + i) != sep) && (*(str + i) != '\0'))
				i++;
			nb++;
		}
		else
			i++;
	}
	return (nb);
}

static size_t	ft_nbc(char const *str, char sep)
{
	size_t i;

	i = 0;
	while ((*(str + i) != sep) && (*(str + i) != '\0'))
		i++;
	return (i);
}

static char		*cpy(char const *src, char sep, size_t size, size_t *count)
{
	size_t		i;
	char		*dest;

	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while ((*(src + i) != sep) && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*count += i;
	*(dest + i) = '\0';
	return (dest);
}

static void		*ft_free_all(char **str, int i)
{
	while (i >= 0)
	{
		free(*(str + i));
		i--;
	}
	free(str);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char		**str;
	size_t		nbr_word;
	size_t		i;
	size_t		nbr;

	if (!s)
		return (NULL);
	nbr_word = ft_nbr_word(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (nbr_word + 1))))
		return (NULL);
	i = 0;
	nbr = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) != c)
		{
			if (!(*(str + nbr) = cpy(s + i, c, ft_nbc(s + i, c), &i)))
				return (ft_free_all(str, i - 1));
			nbr++;
		}
		else
			i++;
	}
	*(str + nbr) = NULL;
	return (str);
}
