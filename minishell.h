/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:33:31 by abarbour          #+#    #+#             */
/*   Updated: 2019/12/03 15:38:02 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_cmd
{
	char 	*path;
	//stat
	int		sep;
	char	*file;
	char	**args;
	int		red;
	int 	built;
	//path0, options,1, null,3
}		t_cmd;

int		get_next_line(int fd, char **line);
t_cmd 	**parser(char *line, char **envp);
int     sep_parser(char *str, t_cmd *tmp);
char    **args_parser(char *path, char *str);
void 	exec(t_cmd ** tab, char **envp);
int 	check_name(char *line, t_cmd *tmp);
char    *cmd_name(char *linep);
int red_type(char *str);


#endif
