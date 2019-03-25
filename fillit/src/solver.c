/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:17:05 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 20:21:09 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

static int	recursive(t_square *sq, t_u8 index)
{
	t_list	*lst;
	t_minos	*tm;
	t_u16	pos;

	lst = ft_lstget(sq->tm_list, index);
	if (lst == NULL)
		return (OK);
	tm = (t_minos *)lst->content;
	pos = 0;
	while (pos < sq->sizexsize)
	{
		tm->pos.x = (pos % sq->size);
		tm->pos.y = (pos / sq->size);
		if (add_tm_to_sq_layout(*tm, sq) == OK)
		{
			if (recursive(sq, index + 1) == OK)
				return (OK);
			else
				rebuild_layout(sq, index);
		}
		++pos;
	}
	return (ERROR);
}

/*
** ft_putstr("index: ");
** ft_putstr(ft_itoa(index));
** ft_putstr(" | pos:(");
** ft_putstr(ft_itoa(tm->pos.x));
** ft_putstr(", ");
** ft_putstr(ft_itoa(tm->pos.y));
** ft_putstr(")\n");
** ft_putstrls((char const**)sq->layout);
** ft_putstr("_____\n");
*/

static int	sqrt_rounded_down(int nb)
{
	int i;

	if (nb <= 0)
		return (0);
	else if (nb == 1)
		return (1);
	i = 2;
	while (i * i < nb)
	{
		++i;
	}
	if (i * i == nb)
		return (i);
	return (i - 1);
}

/*
** Note that 2 is the minimal size for a solution, with the only case being a
** single (e_tmtype)square given as input, but which still needs to be checked.
**	2x2=4  for 1tm=4
**	3x3=9  for 2tm=8
**	4x4=16 for 3tm=12
**	4x4=16 for 4tm=16
**	5x5=25 for 5tm=20
**	5x5=25 for 6tm=24
**	6x6=36 for 7tm=28
**	6x6=36 for 8tm=32 so the min size is "sqrt(tm_amount * 4)"
*/

void		solve(t_list *tm_list)
{
	t_square	*sq;
	int			size;

	sq = NULL;
	size = sqrt_rounded_down(ft_lstsize(tm_list) * 4);
	while (1)
	{
		if (sq)
			del_square(&sq);
		sq = new_square(size, tm_list);
		if (recursive(sq, 0) == OK)
			break ;
		++size;
	}
	ft_putstrls((const char **)(sq->layout));
}
