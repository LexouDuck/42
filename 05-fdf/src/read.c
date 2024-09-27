/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	fdf_readmap_create(t_fdf *fdf, char *file)
{
	t_point	v;
	int		width;
	size_t	i;

	width = 0;
	ft_memclr(&v, sizeof(t_point));
	i = -1;
	while (file[++i])
	{
		if (ft_isspace(file[i]))
		{
			if (v.color || (v.color = 0))
				++v.x;
			if (file[i] == '\n' && (v.y += 1))
			{
				if (width < v.x)
					width = v.x;
				v.x = 0;
			}
		}
		else if (file[i] == '-' || file[i] == '+' || ft_isdigit(file[i]))
			v.color = 1;
	}
	fdf->map_width = width;
	fdf->map_height = v.y + v.color;
}

static void	fdf_readmap_file(char **map, char *file)
{
	t_point	v;
	size_t	length;
	size_t	i;

	v.x = 0;
	v.y = 0;
	i = -1;
	while (file[++i])
	{
		if (file[i] == '-' || file[i] == '+' || ft_isdigit(file[i]))
		{
			length = 1;
			while (file[i + length] && !ft_isspace(file[i + length]))
				++length;
			v.color = (file[i + length] == '\n') ? '\n' : '\0';
			file[i + length] = '\0';
			map[v.y][v.x] = ft_str_to_s8(file + i);
			i += length;
			file[i] = (char)v.color;
			++v.x;
		}
		if (file[i] == '\n' && !(v.x = 0))
			++v.y;
	}
}

char		*fdf_readmap(t_fdf *fdf, int fd)
{
	char	*file;
	t_u32	i;

	if (ft_readfile(fd, &file, 0xFFFFFF))
		return ("Could not read file");
	fdf_readmap_create(fdf, file);
	if (!(fdf->map = (char **)malloc(fdf->map_height * sizeof(char *))))
		return ("Could not create fdf map");
	i = 0;
	while (i < fdf->map_height)
	{
		if (!(fdf->map[i] = (char *)malloc(fdf->map_width * sizeof(char))))
			return ("Could not create fdf map line");
		ft_memclr(fdf->map[i], fdf->map_width * sizeof(char));
		++i;
	}
	fdf_readmap_file(fdf->map, file);
	free(file);
	return (NULL);
}
/*
** ft_putstr(   "width:"); ft_putstr(ft_itoa(fdf->map_width));
** ft_putstr(", height:"); ft_putstr(ft_itoa(fdf->map_height));
** ft_putstr("\n");
** for (t_u32 y = 0; y < fdf->map_height; ++y)
** {
** 	for (t_u32 x = 0; x < fdf->map_width; ++x)
** 		ft_putstr(ft_strpad_l(ft_itoa(fdf->map[y][x]), ' ', 4));
** 	ft_putstr("\n");
** }
*/
