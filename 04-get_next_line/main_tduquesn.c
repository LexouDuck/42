#include "get_next_line.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define CONCURRENT_CHECK TRUE
#define TRUE	1
#define FALSE	0
#define CONSEC	TRUE
#define CONCUR	TRUE

typedef struct		s_fd_info
{
	int			fd;
	int			rdlen;
	char		buf[BUFF_SIZE + 1];
	size_t		bufoffset;
}					t_fd_info;

static int x = 0;

static void		putlstelem_fd_info(t_list *elem)
{
	t_fd_info	*fd_info;

	fd_info = (t_fd_info*)elem->content;
	ft_putstr("Index ");
	ft_putnbr(x++);
	ft_putendl(" :");
	ft_putstr("\t");
	ft_putstr("fd : ");
	ft_putnbr(fd_info->fd);
	ft_putstr("\n\t");
	ft_putstr("bufoffset : ");
	ft_putnbr(fd_info->bufoffset);
	ft_putstr("\n\t");
	ft_putstr("buf : ");
	ft_putendl(fd_info->buf);
	ft_putstr("\n\t");
	ft_putstr("rdlen : ");
	ft_putnbr(fd_info->rdlen);
	ft_putchar('\n');
}

void			putlst_fd_info(t_list *fd_info_lst)
{
	if (!fd_info_lst)
	{
		ft_putendl_fd("Empty fd_info_lst", 2);
		return ;
	}
	x = 0;
	ft_putendl("Displaying file descriptor info :");
	ft_lstiter(fd_info_lst, putlstelem_fd_info);
}

void	exit_error(const char *msg)
{
		if (msg == NULL || msg[0] == '\0')
			ft_putendl_fd("error", 2);
		else
			ft_putendl_fd(msg, 2);
		exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	int		fd;
	int		gnl_status;
	char	*line;

	line = NULL;
	if (argc <= 1)
		exit_error("Not enough args.");

/*
** Consecutive file reading
*/
#if CONSEC

	ft_putendl("\n\n\tCONSECUTIVE File reading: \n");
	for (int i = 1; argv[i]; ++i)
	{
//x = 0;
		if ((fd = open(argv[i], O_RDONLY)) == -1)
			exit_error("Error with call to open: check the filename specified.");
		while ((gnl_status = get_next_line(fd, &line)) == GNL_LINE && ++x < 100)
		{
			ft_putendl(line);
			free(line);
		}
		if (gnl_status == GNL_ERROR)
			exit_error("Error reading file");
		if (close(fd) == -1)
			exit_error("Error closing file");
	}
#endif

/*
** Concurrent file reading
*/
#if CONCUR

	int		done;
	int		fd_hasmore;
	int		fd_arr[argc - 1];


	ft_putendl("\n\n\tCONCURRENT File reading: \n");
	if (argc >= 2 && CONCURRENT_CHECK)
	{

		for (int i = 1; argv[i]; ++i)
		{
			if ((fd = open(argv[i], O_RDONLY)) == -1)
				exit_error("Error with call to open");
			fd_arr[i - 1] = fd;
		}

		done = FALSE;
		while (!done && ++x < 300)
		{
			fd_hasmore = FALSE;
			for (int i = 0; i < argc - 1; ++i)
			{
				if (fd_arr[i] == -1)
					continue ;
				gnl_status = get_next_line(fd_arr[i], &line);
				if (gnl_status == GNL_END)
				{
					ft_putstr("Arrived at the end of file \"");
					ft_putstr(argv[i + 1]);
					ft_putendl("\".");
					if (close(fd_arr[i]) == -1)
						exit_error("Error closing file");
					fd_arr[i] = -1;
				}
				fd_hasmore = fd_hasmore || (gnl_status == 1);
				//ft_putstr("Read from file \"");
				//ft_putstr(argv[i + 1]);
				//ft_putstr("\"\t : ");
				ft_putendl(line);
				free(line);
			}
			done = !fd_hasmore;
		}

	}
#endif
	return (OK);
}
