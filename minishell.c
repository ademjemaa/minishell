/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:47:50 by abarbour          #+#    #+#             */
/*   Updated: 2021/02/22 13:45:49 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		begin_parse_exec(t_cmd ***tab, char ***env_allo, char *line,
char **argv)
{
	(void)argv;
	if (!ft_strncmp(line, "exit", 5))
		return (0);
	*tab = parser(line, *env_allo);
	g_exit_code = 0;
	exec(tab, env_allo, line);
	free_cmds(*tab);
//	write(1, "kembyalet$ ", 12);
	return (1);
}

void	init_minishell(char ***env_allo, char **envp, char **line, int argc)
{
	(void)argc;
	*line = NULL;
	*env_allo = env_start(envp);
	tree_env(*env_allo);
	g_exit_code = 0;
	g_childs = 0;
//	write(1, "kembyalet$ ", 12);
	catch_signals(0);
}

int		exit_minishell(char **env_allo)
{
	free_env(env_allo, str_array_len(env_allo));
	return (g_exit_code);
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
			if (!begin_parse_exec(&tab, &env_allo, line, argv))
			{
				free(line);
				break ;
			}
			free(line);
		}
		else
		{
			write(1, "exit\n", 5);
			break ;
		}
	}
	return (exit_minishell(env_allo));
}
