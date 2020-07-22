/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:14:06 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/18 22:59:58 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_handler(int signum)
{
	exit_code = 1;
}

void	catch_signals()
{
	signal(SIGINT, &int_handler);
}
