/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:52:17 by abarbour          #+#    #+#             */
/*   Updated: 2020/08/09 18:09:52 by adjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		counter(char *line)
{
	int total;
	int i;

	total = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == ';')
			total++;
		i++;
	}
	return (total);
}

char	*cmd_name(char *line)
{
	int		i;
	int		nb_c;
	char	*str;

	i = 0;
	nb_c = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			nb_c += nb_remove_sq(line, &i);
		if (line[i] == '\"')
			nb_c += nb_remove_dq(line, &i);
		else if (line[i])
		{
			nb_c++;
			i++;
		}
	}
	return (create_cmd_name(line, nb_c));
}

void	print_structure(t_cmd *tmp)
{
	int i;

	i = 0;
	printf("structure : \n");
	if (tmp->path)
		printf("path == %s!!\n", tmp->path);
	if (tmp->file)
		printf("file == %s!!\n",  tmp->file);
	if (tmp->args)
	{
		while (tmp->args[i] != NULL)
		{
			printf("args == !!%s!!\n", tmp->args[i]);
		i++;
   		 }
	}
	i = 0;
	 while (tmp->files[i].file != NULL)
	{
		printf("files == %s\n", tmp->files[i].file);
		i++;
	}
	printf("sep == %d\nred == %d\nbuild == %d\n", tmp->sep, tmp->red, tmp->built);
}

char	*path_parser(char *line, char **envp, t_cmd *tmp)
{
	char			*stri;
	struct stat		sb;
	int				i;

	tmp->built = 0;
	i = 0;
	tmp->prog = 0;
	stri = cmd_name(line);
	if (stri == NULL)
		return (NULL);
	while (stri[i] && stri[i] != '/')
		i++;
	if (stri[i] == '/')
	{
		tmp->prog = 1;
		if (stat(&stri[i + 1], &sb) == 0)
			return (stri);
	}
	if (check_name(line, tmp))
		return (stri);
	free(stri);
	return (ret_handler(line, envp, &sb));
}

t_cmd	*params(char *line, char **envp)
{
	t_cmd	*tmp;
	char	*str;

	tmp = (t_cmd*)malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (NULL);
	init_tmp(tmp);
	str = args_parser(line, envp, tmp);
	tmp->red = red_type(str);
	print_structure(tmp);
	free(str);
	return (tmp);
}

t_cmd	**parser(char *line, char **envp)
{
	int		total;
	t_cmd	**tab;
	int		i;
	int		j;

	i = 0;
	total = counter(line);
	j = 0;
	tab = (t_cmd**)malloc(sizeof(t_cmd**) * (total + 1));
	if (tab == NULL)
		return (NULL);
	while (line[j])
	{
		tab[i] = params(&line[j], envp);
		i++;
		while (line[j] && line[j] != '|' && line[j] != ';')
			if (line[j++] == '\\')
				j++;
		if (line[j])
			j++;
	}
	tab[i] = NULL;
	return (tab);
}
