/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "02-libft/libft.h"

# define GNL_ERROR -1
# define GNL_LINE	1
# define GNL_END	0

# define BUFF_SIZE 1024

#endif

static	int		gnl_read_file(int const fd, char *tmp[fd])
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;

	result = 0;
	while (ft_strchr(tmp[fd], '\n') == NULL &&
		(result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		temp = tmp[fd];
		if (!(tmp[fd] = ft_strjoin(temp, buffer)))
			return (0);
		free(temp);
	}
	return (result);
}

static	int		gnl_make_line(int const fd, char *tmp[fd], char **line)
{
	int		space;
	char	*str;

	space = 0;
	str = tmp[fd];
	while (str[space])
	{
		if (str[space] == '\n')
			break ;
		++space;
	}
	str = NULL;
	*line = ft_strsub(tmp[fd], 0, space);
	if (!(str = (char *)malloc(sizeof(str) * (ft_strlen(tmp[fd]) + 1))))
		return (GNL_ERROR);
	ft_strcpy(str, &tmp[fd][space + 1]);
	ft_strclr(tmp[fd]);
	tmp[fd] = ft_strcpy(tmp[fd], str);
	free(str);
	return (GNL_LINE);
}

int				get_next_line(int const fd, char **line)
{
	static	char	*tmp[256];

	if (line == NULL || BUFF_SIZE < 0 || fd < 0 || fd > 256)
		return (GNL_ERROR);
	if (tmp[fd] == NULL && (tmp[fd] = ft_strnew(2)) == NULL)
		return (GNL_ERROR);
	if (gnl_read_file(fd, &(*tmp)) < 0)
		return (GNL_ERROR);
	if (tmp[fd][0] == '\0')
	{
		*line = NULL;
		return (GNL_END);
	}
	if (gnl_make_line(fd, tmp, line) < 0)
		return (GNL_ERROR);
	return (GNL_LINE);
}
/*
** ft_putstr("debug->offset:");
** ft_putstr(ft_strpad_l(ft_itoa(offset), ' ', 2));
** ft_putstr(     ", length:");
** ft_putstr(ft_strpad_l(ft_itoa(length), ' ', 2)); ft_putstr(" | ");
*/

int				read_file(int const fd, char **file)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	result = 0;
	*file = (char *)malloc(1);
	**file = '\0';
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		tmp = *file;
		if ((*file = ft_strjoin(tmp, buffer)) == NULL)
			return (GNL_ERROR);
		free(tmp);
	}
	return (result);
}
