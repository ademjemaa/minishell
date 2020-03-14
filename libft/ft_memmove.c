/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 09:26:24 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/12 15:52:16 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	unsigned char	*str_dst;
	unsigned char	*str_src;
	size_t			i;

	if (!(str_dst = dst) && !src)
		return (NULL);
	str_src = (unsigned char *)src;
	if ((str_src < str_dst) && (str_src + len - 1 > str_dst))
	{
		i = len + 1;
		while (--i > 0)
			str_dst[i - 1] = str_src[i - 1];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			str_dst[i] = str_src[i];
			i++;
		}
	}
	return (dst);
}
