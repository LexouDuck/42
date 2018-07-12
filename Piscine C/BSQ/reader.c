/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:55:14 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 22:17:57 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		read_map(char *filepath)
{
	int			file_desc;
	int			filesize;
	char		**map_strls;
	t_tiles		*tiles;
	t_square	bsq;

	map_strls = NULL;
	if (!(tiles = (t_tiles*)malloc(sizeof(t_tiles))))
		return (ERROR);
	if (ft_strcmp(filepath, "stdin") == 0)
		file_desc = 0;
	else if ((file_desc = open(filepath, O_RDONLY)) == -1)
		return (ERROR);
	if (!(map_strls = make_map(file_desc, &filesize, tiles, &bsq)))
		return (ERROR);
	filesize = solve(&bsq, tiles, map_strls);
	filesize += close(file_desc) * -1;
	return (filesize);
}

t_chunk	*make_linked_list(int fd, int *filesize)
{
	int		length;
	char	*buffer;
	t_chunk	*curr_chunk;
	t_chunk	*chunklist;

	*filesize = 0;
	chunklist = 0;
	if (!(buffer = (char*)malloc(BUFFER_SIZE + 1)))
		return (NULL);
	while ((length = read(fd, buffer, BUFFER_SIZE)))
	{
		*filesize += length;
		if (!(curr_chunk = (t_chunk*)malloc(sizeof(t_chunk))))
			return (NULL);
		curr_chunk->size = length;
		if (!(curr_chunk->str = (char*)malloc(BUFFER_SIZE + 1)))
			return (NULL);
		ft_strncpy(curr_chunk->str, buffer, length + 1);
		curr_chunk->next = chunklist;
		if (chunklist != 0)
			chunklist->prev = curr_chunk;
		chunklist = curr_chunk;
		chunklist->prev = 0;
	}
	return (chunklist);
}

char	*concat_mapstr(t_chunk *llist, int filesize)
{
	char	*mapstr;
	t_chunk	*curr_chunk;

	if (!(mapstr = (char*)malloc(filesize)))
		return (NULL);
	curr_chunk = llist;
	while (curr_chunk->next)
		curr_chunk = curr_chunk->next;
	while (curr_chunk->prev)
	{
		free(curr_chunk->next);
		ft_strcat(mapstr, curr_chunk->str);
		curr_chunk = curr_chunk->prev;
	}
	ft_strncat(mapstr, curr_chunk->str, curr_chunk->size);
	ft_strncpy(mapstr, mapstr, filesize);
	mapstr[filesize] = '\0';
	free(curr_chunk);
	return (mapstr);
}

char	**make_map(int file_desc, int *filesize, t_tiles *tiles, t_square *bsq)
{
	t_chunk	*llist;
	char	*mapstr;
	char	**strls;
	char	**map;

	if (!(llist = make_linked_list(file_desc, filesize)))
		return (NULL);
	if (!(mapstr = concat_mapstr(llist, *filesize)))
		return (NULL);
	strls = split_map(mapstr, "\n");
	free(mapstr);
	if (check_map(strls, tiles, &(bsq->map_w), &(bsq->map_h)))
		return (NULL);
	map = strls + 1;
	return (map);
}
