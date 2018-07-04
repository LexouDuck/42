#include "get_next_line.c"

#include <fcntl.h>
// These two are only required on some UNIX distribs
#include <sys/types.h>
#include <sys/stat.h>

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;

	i = 1;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putendl("get_next_line: could not open file");
			return (ERROR);
		}
		int result;
		char *str;
		char *tmp;
		line = NULL;
		while ((result = get_next_line(fd, &line)) == GNL_LINE)
		{
			tmp = ft_itoa(i);
			str = ft_strpad_l(tmp, ' ', 4);
			ft_putstr(str);
			ft_putstr(" |");
			ft_putendl(line);
			free(line);
			free(str);
			free(tmp);
			//line = NULL;
			++i;
		}
		if (result == GNL_ERROR)
			ft_putendl("get_next_line: error");
	}
	else ft_putendl("get_next_line: expecting one filepath argument");
}
