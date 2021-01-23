/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 00:08:49 by abarbour          #+#    #+#             */
/*   Updated: 2021/01/23 13:27:38 by abarbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <sys/errno.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>

typedef struct	s_filelst
{
	int		red;
	char	*file;
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
	char		*path;
	int			sep;
	char		*file;
	int			prog;
	char		**args;
	t_filelst	*files;
	int			red;
	int			built;
}				t_cmd;

int				g_exit_code;
int				g_childs;

int				backslash(char *str, char *tmp, int *i, int cond);
int				arg_handler(char *str, char *tmp, int *i);
void			quotes_cal(char *line, int *i);
char			*copy_clean(char *tmp, char *str);
int				envp_len(char *str, char *tmp);
int				find_filered(char *str);
int				env_len(char *str);
char			**first_split(char *line);
char			*file_prot(char *str, char *tmp, int *j);
int				line_return(char *str);
int				quote_status(t_check *c, char *str);
char			*cleaned(char *str);
int				get_next_line(int fd, char **line);
char			*rearrange(char *str);
char			*retrieve(char *str, char **envp);
void			free_all(char **args);
t_cmd			**parser(char *line, char **envp);
int				final_size(char *str, char *envp);
int				check_cmd(char **args, int j);
t_filelst		*find_filelst(char **args, char **envp);
void			copy_slash(char *tmp, char *str, t_check *c);
void			init_struct(t_check *c);
void			envp_slash(char *str, char *tmp, t_check *c, char *envp);
int				sep_parser(char *str, t_cmd *tmp);
char			*args_parser(char *str, char **envp, t_cmd *stru);
void			find_env(char **args, char **envp);
char			**find_path(char **args, t_cmd *tmp, char **envp);
char			*path_parser(char *line, char **envp, t_cmd *tmp);
void			exec(t_cmd ***tab, char ***envp, char *line);
void			dup_and_close(int in, int out);
int				check_name(char *line, t_cmd *tmp);
int				fix_quotes(t_check *check, char *str);
void			quote_limits(char *str, int *i, int *j);
void			copy_quotes(char *str, char *tmp, t_check *c);
char			*cmd_name(char *linep);
int				red_type(char *str);
void			init_tmp(t_cmd *tmp);
char			*exact_env(char *str);
char			*ret_handler(char *line, char **envp, struct stat *sb);
int				ft_strcmp(char *s1, char *s2);
int				nargs_count(char **args);
void			concat_args(t_cmd *cmd);
void			concat_sbs_args(t_cmd *cmd, char **new_args, int *i, int *j);
char			*proc_arg(char **args, int i);
int				narg_len_dq(char *arg);
int				narg_len_sq(char *arg);
void			rd_cr_files(t_cmd *cmd, int *in, int *out);
void			free_cmds(t_cmd **tab);
void			ft_putstr_error(char *str);
int				narg_len_nq(char *arg);
char			*swap_case(char *args, char **envp, int j);
char			*change_str(char *envp, char *str);
void			catch_signals();
int				rd_files(t_cmd *cmd, int in);
int				exec_built_in(int in, int out, t_cmd *tab, char ***envp);
int				exec_pipe(t_cmd **tab, int *i, char ***envp);
int				is_env_built_in_cmd(t_cmd **tab, int i);
int				ft_echo(char *path, char **args, char **envp);
int				ft_pwd(char *path, char **args, char **envp);
int				ft_env(char *path, char **args, char **env);
int				ft_cd(char *path, char **args, char **envp);
int				ft_exit(char *path, char **args, char ***envp);
int				ft_export(char *path, char **args, char ***envp, int p);
int				ft_unset(char *path, char **args, char ***envp, int p);
char			**env_start(char **envp);
int				dispatch_built_in(t_cmd *cmd, char ***envp, int p);
int				equal_pos(char *var);
void			update_env(char *var, char **envp, int i);
void			add_env(char *var, char ***envp);
char			*free_env(char **env, int i);
int				str_array_len(char **envp);
void			tree_env(char **envp);
void			begin_pipe(t_cmd **tab, char ***envp, int *i);
char			*create_cmd_name(char *line, int nb_c);
int				nb_remove_dq(char *line, int *i);
int				nb_remove_sq(char *line, int *i);
void			add_var_to_env(char *var, char ***envp);
char			*trait_after_export(char **str);

#endif
