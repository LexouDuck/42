/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 16:47:30 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 17:58:59 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER 1024

typedef struct	s_map
{
	char	**str;
	int		width;
	int		height;
}				t_map;

t_map *read_file(char *filepath)
{
	int file = open(filepath, O_RDONLY);
	t_map *result;
	result = malloc(sizeof(t_map));
	char **map;
	char *buffer;
	map = malloc((BUFFER + 1) * sizeof(char*));
	map[BUFFER] = NULL;
	map[0] = malloc(BUFFER);
	buffer = malloc(1);
	int n = 0;
	int i = 0;
	while (read(file, buffer, 1) > 0)
	{
		if (buffer[i] != '.' &&
			buffer[i] != 'X' &&
			buffer[i] != '\n' &&
			buffer[i] != '\0')
		{
			return (NULL);
		}
		else if (buffer[i] == '\n')
		{
			if (result->width == 0)
				result->width = i;
			else if (i != result->width)
			{
				write(1, "error2", 6);
				return (NULL);
			}
			map[n][i] = '\0';
			i = 0;
			n++;
			map[n] = malloc(BUFFER);
		}
		else map[n][i++] = *buffer;
		free(buffer);
		buffer = malloc(BUFFER);
	}
	free(buffer);
	result->height = n;
	result->str = map;
	return (result);
}

void flood_fill(t_map *map, char *c, int x, int y)
{
	if (x >= 0 && x < map->width &&
		y >= 0 && y < map->height &&
		map->str[y][x] == 'X')
	{
		map->str[y][x] = *c;
		flood_fill(map, c, x + 1, y);
		flood_fill(map, c, x - 1, y);
		flood_fill(map, c, x, y + 1);
		flood_fill(map, c, x, y - 1);
	}
	else return;
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_map *map = read_file(argv[1]);
		if (map == NULL)
		{
			write(1, "\n", 1);
			return (0);
		}
		char c = '0';
		for (int y = 0; map->str[y]; y++)
		for (int x = 0; map->str[y][x]; x++)
		{
			if (map->str[y][x] == 'X')
			{
				flood_fill(map, &c, x, y);
				c++;
			}
			write(1, &c, 1);
		}
	}
	else write(1, "\n", 1);
	return (0);
}
