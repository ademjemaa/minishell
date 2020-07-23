/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:33:31 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/23 22:31:12 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <sys/errno.h>
# include <string.h>

typedef struct	s_filelst
{
	int red;
	char *file;
}				t_filelst;

typedef struct	s_check
{
	int i;
	int j;
	int env;
	int one;
	int two;
}				t_check;

typedef struct	s_cmd
{
	char 		*path;
	int			sep;
	char		*file;
	char		**args;
	t_filelst	*files;
	int			red;
	int 		built;
}				t_cmd;

int		exit_code;
int		backslash(char *str, char *tmp, int *i, int cond);
int		arg_handler(char *str, char *tmp, int *i);
void	quotes_cal(char *line, int *i);
char	*copy_clean(char *tmp, char *str);
int		envp_len(char *str, char *tmp);
int		find_filered(char *str);
int		env_len(char *str);
char	**first_split(char *line);
char	*file_prot(char *str, char *tmp, int *j);
int		line_return(char *str);
int		quote_status(t_check *c, char *str);
char	*cleaned(char *str);
int		get_next_line(int fd, char **line);
char    *rearrange(char *str);
char	*retrieve(char *str, char **envp);
void    free_all(char **args);
t_cmd 	**parser(char *line, char **envp);
int		final_size(char *str, char *envp);
t_filelst    *find_filelst(char **args, char **envp);
int     sep_parser(char *str, t_cmd *tmp);
void	args_parser(char *str, char **envp, t_cmd *stru);
void 	find_env(char **args, char **envp);
char    **find_path(char **args, t_cmd *tmp, char **envp);
char    *path_parser(char *line, char **envp, t_cmd *tmp);
void 	exec(t_cmd ** tab, char **envp);
int 	check_name(char *line, t_cmd *tmp);
char    *cmd_name(char *linep);
int 	red_type(char *str);
char	*exact_env(char *str);
int		ft_strcmp(char *s1, char *s2);
int		nargs_count(char **args);
void	concat_args(t_cmd *cmd);
void    print_structure(t_cmd *tmp);
int		narg_len_dq(char	*arg);
int		narg_len_sq(char	*arg);
int		cr_files(t_cmd *cmd, int out);
void	free_cmds(t_cmd **tab);
void	ft_putstr_error(char *str);
int		narg_len_nq(char *arg);
char	*swap_case(char *args, char **envp, int j);
char	*change_str(char *envp, char *str);
void	catch_signals();
int		rd_files(t_cmd *cmd, int in);

#endif
