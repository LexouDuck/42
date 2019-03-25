/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:16:39 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 19:19:28 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

void	exit_error(const char *msg)
{
	if (msg == NULL || msg[0] == '\0')
		ft_putstr("error\n");
	else
		ft_putstr(msg);
	exit(EXIT_FAILURE);
}

void	display_tm(t_minos *tm)
{
	int			e;
	char const	**layout;

	e = tm->type;
	ft_putstr("\n--- Type enum number :\n\t");
	ft_putnbr(e);
	ft_putstr("\n--- Layout :\n");
	layout = (char const**)ft_strlspad_left((char const**)tm->layout, '\t', 1);
	ft_putstrls(layout);
	ft_strlsdel((char***)&layout);
	ft_putstr("--- Index in list (-1 if lone tm) :\n\t");
	ft_putnbr(tm->index);
	ft_putstr("\n--- Size\n\tsize.y : ");
	ft_putnbr(tm->size.y);
	ft_putstr("\n\tsize.x : ");
	ft_putnbr(tm->size.x);
	ft_putstr("\n\n");
}

void	display_tm_lstelem(t_list *tm_lstelem)
{
	display_tm((t_minos*)(tm_lstelem->content));
}

void	display_tm_list(t_list *tm_list)
{
	ft_lstiter(tm_list, display_tm_lstelem);
}

int		main(int argc, char **argv)
{
	t_list *tm_list;

	if (argc != 2)
		exit_error("fillit: expecting single file operand\n");
	tm_list = read_fillit_file(argv[1]);
	solve(tm_list);
	return (0);
}
/*
** ft_lstdel(tm_list, delete_tm_list);
** delete_tm_list faut coder si on veut etre leak free,
** faut strlsdel le tm->layout de chaque layout en gros
*/
