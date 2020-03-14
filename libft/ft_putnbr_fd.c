/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:47:21 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/12 15:39:22 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_digit(int i, int fd)
{
	if (i < 0)
		i = -i;
	i = i + 48;
	write(fd, &i, 1);
}

static void	ft_putnbr_rec(int nb, int fd)
{
	if (nb / 10 != 0)
		ft_putnbr_rec(nb / 10, fd);
	ft_put_digit(nb % 10, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	ft_putnbr_rec(n, fd);
}
