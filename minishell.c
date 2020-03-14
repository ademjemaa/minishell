#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	argc = argc;
	argv =argv ;
	envp =envp ;
	line = NULL;
	write(1,"kembyalet$",11);
	while(1)
	{
		get_next_line(0, &line);
		if(line)
		{
			if(!ft_strncmp(line, "exit", 5))
			{
				free(line);
				exit(0);
			}
			write(1,"kembyalet$",11);
			free(line);
		}
	}
	return (0);
}
