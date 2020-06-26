/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:47:50 by abarbour          #+#    #+#             */
/*   Updated: 2020/06/27 00:14:17 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			ret;
	t_cmd 		**tab;

	line = NULL;
	(void)argc;
	write(1,"kembyalet$",11);
	write(1, argv[1], 3);
	while(1)
	{
		//get_next_line fih segfault, jarab ikteb b "ls || cat" fil ./a.out
		//adem : testi cat libft/*, i9olik error ema normalment ti5dem, mahouch 9a3ed ichouf fil *, normal ?
		ret = get_next_line(0, &line);
		if(line && ret > 0)
		{
			if(!ft_strncmp(line, "exit", 5))
			{
				free(line);
				exit(0);
			}
			tab = parser(line, envp);
			printf("parsing done\n");
			//exec(tab, envp);
			free_cmds(tab);
	    	write(1,"kembyalet$",11);
			free(line);
		}
		else
		{
			write(1, "\n", 1);
			break;
		}
	}
	return (0);
}
