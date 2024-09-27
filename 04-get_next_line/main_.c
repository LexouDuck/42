/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfleming <tfleming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 11:52:59 by tfleming          #+#    #+#             */
/*   Updated: 2014/11/25 23:08:07 by tfleming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int				get_next_line(int const fd, char **line);

#define TF_DEBUG		1

void			test(char *filename)
{
	int		fd;
	int		outfd;
	char	*line;
	int		returned;

	if (TF_DEBUG)
	{
		printf("===========================================================\n");
		printf("filename = %s\n", filename);
	}
	fd = open(filename, O_RDONLY);
	outfd = open("this_out.txt", O_WRONLY | O_TRUNC);
	line = NULL;
	while ((returned = get_next_line(fd, &line)) == 1)
	{
		if (TF_DEBUG) printf("returned = \t|%s|\n", line);
		dprintf(outfd, "%s\n", line);
		free(line);
		line = NULL;
	}
	if (TF_DEBUG) printf("last = \t\t|%s|\n", line);
	if (line)
	{
		dprintf(outfd, "%s", line);
		free(line);
	}
	if (returned != 0) printf("ERROR: Did not return 0 at the end\n");
	returned = get_next_line(fd, &line);
	if (returned != 0) printf("repeated calls failing\n");
	close(outfd);
	close(fd);
	if (TF_DEBUG) printf("=================================================\n");
}

int				main(int argc, char **argv)
{
	char		*fake_line;

	if (argc != 2)
	{
		if (argc == 3)
		{
			if (get_next_line(42, &fake_line)  == -1)
				printf("done testing fake fd\n");
			else
				printf("ERROR: did not pass fake fd test\n");
		}
		else
			printf("incorrect arguments to testing program=====\n");
		return (1);
	}
	test(argv[1]);
	return (0);
}
