/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:16:57 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 20:18:39 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Check input file symbol and format correctness, not logical correctness,
** of input file
*/

static void	check_input_file(const char *filedata)
{
	int		c;
	int		x;
	int		y;

	c = 0;
	x = 0;
	y = 0;
	while (filedata[c + x])
	{
		if (x < 5)
		{
			if ((x == 4 && filedata[c + x] != '\n') ||
				(x < 4 && filedata[c + x] != '#' && filedata[c + x] != '.'))
				exit_error("");
			x++;
		}
		else
		{
			c += 5;
			if (y == 3 && filedata[c++] != '\n')
				exit_error("");
			y = (y + 1) % 4;
			x = 0;
		}
	}
}

t_list		*read_fillit_file(const char *filepath)
{
	int			fd;
	int			filesize;
	char		*filedata;
	t_list		*tm_list;

	if ((fd = open(filepath, O_RDONLY)) == -1)
		exit_error("");
	if (!(filedata = (char*)malloc(MAX_VALID_FILE_SIZE)))
		exit_error("");
	if ((filesize = read(fd, filedata, MAX_VALID_FILE_SIZE)) == -1)
		exit_error("");
	if (filesize == MAX_VALID_FILE_SIZE || close(fd) == -1)
		exit_error("");
	filedata[filesize + 1] = '\0';
	check_input_file((const char*)filedata);
	tm_list = new_lst_tminos((const char*)filedata);
	ft_strdel(&filedata);
	if (!tm_list)
		exit_error("");
	return (tm_list);
}
