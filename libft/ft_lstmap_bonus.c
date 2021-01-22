/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:06:00 by abarbour          #+#    #+#             */
/*   Updated: 2019/11/13 12:45:24 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *nlst;
	t_list *i;

	nlst = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!(i = (t_list *)malloc(sizeof(t_list))))
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		i->content = (*f)(lst->content);
		ft_lstadd_back(&nlst, i);
		lst = lst->next;
	}
	return (nlst);
}
