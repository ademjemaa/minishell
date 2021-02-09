/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:57:18 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/09 16:11:02 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t dest_len;
	size_t i;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dest_len + 1 > dstsize)
		return (dstsize + src_len);
	i = 0;
	while ((*(src + i) != '\0') && (i < dstsize - dest_len - 1))
	{
		*(dst + dest_len + i) = *(src + i);
		i++;
	}
	*(dst + dest_len + i) = '\0';
	return (dest_len + src_len);
}
