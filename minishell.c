#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret;

	argc = argc;
	argv =argv ;
	envp =envp ;
	line = NULL;
	write(1,"kembyalet$",11);
	write(1, argv[1], 3);
	while(1)
	{
		ret = get_next_line(0, &line);
		if(line && ret > 0)
		{
			if(!ft_strncmp(line, "exit", 5))
			{
				free(line);
				exit(0);
			}
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
