/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_t_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:17:42 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 20:27:32 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

t_square		*new_square(int size, t_list *tm_list)
{
	t_square	*result;

	if (!(result = (t_square*)malloc(sizeof(t_square))))
		return (NULL);
	result->size = size;
	result->sizexsize = size * size;
	result->layout = ft_strlsnew(size, size, '.');
	result->tm_list = tm_list;
	result->tmlst_size = ft_lstsize(tm_list);
	return (result);
}

void			del_square(t_square **sq)
{
	if (*sq)
	{
		ft_strlsdel(&((*sq)->layout));
		free(*sq);
		*sq = NULL;
	}
}

int				add_tm_to_sq_layout(t_minos const tm, t_square *sq)
{
	t_u8	i;
	t_u8	j;

	if (overlap(tm, *sq))
		return (ERROR);
	i = 0;
	while (tm.layout[i])
	{
		j = 0;
		while (tm.layout[i][j])
		{
			if (tm.layout[i][j] == '#')
				sq->layout[tm.pos.y + i][tm.pos.x + j] = 'A' + tm.index;
			++j;
		}
		++i;
	}
	return (OK);
}

void			rebuild_layout(t_square *sq, t_u8 index)
{
	t_u8	i;
	t_u8	j;

	i = 0;
	while (sq->layout[i])
	{
		j = 0;
		while (sq->layout[i][j])
		{
			if (sq->layout[i][j] >= 'A' + index)
				sq->layout[i][j] = '.';
			++j;
		}
		++i;
	}
}

void			display_square(t_square *sq)
{
	char const	**layout;

	ft_putstr("\n--- Size\n\t");
	ft_putnbr(sq->size);
	ft_putstr("\n--- Current layout :\n");
	layout = (char const**)ft_strlspad_left((char const**)sq->layout, '\t', 1);
	ft_putstrls(layout);
	ft_strlsdel((char***)&layout);
	ft_putstr("--- Size of tm_list :\n\t");
	ft_putnbr(sq->tmlst_size);
	ft_putstr("\n\n");
}
