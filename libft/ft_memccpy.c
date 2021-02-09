/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:31:40 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/11 15:00:41 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*str_dst;
	char	*str_src;

	i = 0;
	if (!dst && !src)
		return (NULL);
	str_src = (char *)src;
	str_dst = (char *)dst;
	while ((i < n) && ((unsigned char)str_src[i] != (unsigned char)c))
	{
		str_dst[i] = (unsigned char)str_src[i];
		i++;
	}
	if ((unsigned char)str_src[i] == (unsigned char)c)
	{
		str_dst[i] = (unsigned char)str_src[i];
		return (dst + i + 1);
	}
	return (NULL);
}
