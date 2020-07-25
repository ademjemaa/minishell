/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbour <abarbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:52:17 by abarbour          #+#    #+#             */
/*   Updated: 2020/07/26 00:13:39 by adjemaa          ###   ########.fr       */
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
	int		j;
	char	*str;

	j = 0;
	if (line == NULL)
		return (NULL);
	while (line[j] == ' ' && line[j])
		j++;
	i = j;
	while (line[i] && line[i] != ' ')
		i++;
	str = malloc(sizeof(char) * (i - j + 1));
	str[i - j] = '\0';
	i = 0;
	while (line[j] != ' ' && line[j])
		str[i++] = line[j++];
	str[i] = 0;
	return (str);
}

char	*path_parser(char *line, char **envp, t_cmd *tmp)
{
	char			*stri;
	struct stat		sb;

	tmp->built = 0;
	stri = cmd_name(line);
	if (stri == NULL)
		return (NULL);
	if (check_name(line, tmp))
		return (stri);
	if (stat(stri, &sb) == 0)
		return (stri);
	free(stri);
	return (ret_handler(line, envp, &sb));
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

t_cmd	*params(char *line, char **envp)
{
	t_cmd	*tmp;
	char	*str;

	tmp = (t_cmd*)malloc(sizeof(t_cmd));
	str = args_parser(line, envp, tmp);
	tmp->sep = sep_parser(str, tmp);
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
	while (line[j])
	{
		tab[i] = params(&line[j], envp);
		i++;
		while (line[j] && line[j] != '|' && line[j] != ';')
			j++;
		if (line[j])
			j++;
	}
	tab[i] = NULL;
	return (tab);
}
