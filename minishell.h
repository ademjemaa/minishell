/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:33:31 by abarbour          #+#    #+#             */
/*   Updated: 2020/05/28 21:08:10 by adjemaa          ###   ########.fr       */
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
	char	**files;
	int		red;
	int 	built;
	//path0, options,1, null,3
}		t_cmd;

char	*copy_clean(char *tmp, char *str);
char	**first_split(char *line);
int		quote_status(int *one, int *two, int *i, char *str);
char	*cleaned(char *str);
int		get_next_line(int fd, char **line);
char    *rearrange(char *str);
void    free_all(char **args);
t_cmd 	**parser(char *line, char **envp);
int		final_size(char *str, char *envp);
char    **find_filelst(char **args);
int     sep_parser(char *str, t_cmd *tmp);
void	args_parser(char *str, char **envp, t_cmd *stru);
void 	find_env(char **args, char **envp);
char    **find_path(char **args, t_cmd *tmp, char **envp);
char    *path_parser(char *line, char **envp, t_cmd *tmp);
void 	exec(t_cmd ** tab, char **envp);
int 	check_name(char *line, t_cmd *tmp);
char    *cmd_name(char *linep);
int red_type(char *str);
char	*exact_env(char *str);

#endif
