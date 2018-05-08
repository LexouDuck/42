#include "get_next_line.h"

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
		line = NULL;
		while (get_next_line(fd, &line) == GNL_LINE)
		{
			ft_putstr(ft_strpad_l(ft_itoa(i), ' ', 4));
			ft_putstr(" |");
			ft_putendl(line);
			free(line);
			//line = NULL;
			++i;
		}
	}
	else ft_putendl("get_next_line: expecting one filepath argument");
}
