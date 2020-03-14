/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:28:48 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/13 12:21:13 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*i;

	new->next = NULL;
	if (!(*alst))
		*alst = new;
	else
	{
		i = *alst;
		while (i->next)
			i = i->next;
		i->next = new;
	}
}
