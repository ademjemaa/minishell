/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:47:50 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/07 22:06:10 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	begin_parse_exec(t_cmd ***tab, char ***env_allo, char **line)
{
	*tab = parser(*line, *env_allo);
	exec(*tab, env_allo);
	free_cmds(*tab);
	write(1, "kembyalet$ ", 12);
	free(*line);
}

void	init_minishell(char ***env_allo, char **envp, char **line, int argc)
{
	*line = NULL;
	*env_allo = env_start(envp);
	tree_env(*env_allo);
	g_exit_code = 0;
	write(1, "kembyalet$ ", 12);
	catch_signals(0);
}

int		main(int argc, char **argv, char **envp)
{
	char		*line;
	int			ret;
	t_cmd		**tab;
	char		**env_allo;

	init_minishell(&env_allo, envp, &line, argc);
	while (1)
	{
		ret = get_next_line(0, &line);
		if (line && ret > 0)
		{
			if (!ft_strncmp(line, "exit", 5))
			{
				free(line);
				break ;
			}
			begin_parse_exec(&tab, &env_allo, &line);
		}
		else
		{
			write(1, "exit\n", 5);
			break ;
		}
	}
	return (g_exit_code);
}
