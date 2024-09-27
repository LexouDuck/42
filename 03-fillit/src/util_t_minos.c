/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_t_minos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:17:30 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 20:42:35 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

static int		count_adjacencies(const char **tm_4by4, int y, int x)
{
	int		count;

	count = 0;
	if (pt_in_bounds(4, 4, y, x - 1))
		if (tm_4by4[y][x - 1] == '#')
			++count;
	if (pt_in_bounds(4, 4, y - 1, x))
		if (tm_4by4[y - 1][x] == '#')
			++count;
	if (pt_in_bounds(4, 4, y, x + 1))
		if (tm_4by4[y][x + 1] == '#')
			++count;
	if (pt_in_bounds(4, 4, y + 1, x))
		if (tm_4by4[y + 1][x] == '#')
			++count;
	return (count);
}

/*
** Necessary condition for being a piece: at least 1 element has at least
** 2 adajacent elements AND all elements have at least 1 adjacent element.
*/

static void		verify_tminos(const char **tm_4by4)
{
	int		i;
	int		j;
	int		block_count;
	int		adj_block_tab[4];

	if (ft_strls_countchar(tm_4by4, '#') != 4)
		exit_error("");
	block_count = 0;
	i = -1;
	while (tm_4by4[++i])
	{
		j = -1;
		while (tm_4by4[i][++j])
			if (tm_4by4[i][j] == '#')
				adj_block_tab[block_count++] = count_adjacencies(tm_4by4, i, j);
	}
	i = -1;
	while (++i < 4)
		if (adj_block_tab[i] == 0)
			exit_error("");
		else if (adj_block_tab[i] >= 2)
			j = 42;
	if (j != 42)
		exit_error("");
}

static t_minos	*new_tminos(const char **tm_4by4)
{
	t_minos		*result;
	t_u8		i;
	char		**strls;

	if (!(result = (t_minos*)malloc(sizeof(t_minos))))
		exit_error("");
	result->type = DIFF_PIECE_NB;
	i = -1;
	while (++i < DIFF_PIECE_NB)
	{
		strls = tmtype_to_strls(i);
		result->size = ft_newpoint(ft_ptrarrlen(strls), ft_strlen(strls[0]));
		if (str_2d_match((const char**)strls,
					tm_4by4, result->size, ft_newpoint(4, 4)))
		{
			result->type = (t_tmtype)i;
			result->layout = (const char**)strls;
			break ;
		}
		ft_strlsdel(&strls);
	}
	if (result->type == DIFF_PIECE_NB)
		exit_error("");
	result->index = (t_u8)(-1);
	return (result);
}

t_list			*new_lst_tminos(char const *filedata)
{
	t_u32		i;
	char		**inputfile_strls;
	char		**cur_elem_strls;
	t_list		*tm_list;
	t_list		*cur_elem;

	tm_list = 0;
	if (!(inputfile_strls = ft_split(filedata, "\n")))
		exit_error("");
	i = 0;
	while (inputfile_strls[i])
	{
		cur_elem_strls = ft_strlssub((char const **)inputfile_strls, i, 4);
		verify_tminos((char const **)cur_elem_strls);
		cur_elem = ft_lstnew(
				new_tminos((char const **)cur_elem_strls), sizeof(t_minos));
		ft_strlsdel(&cur_elem_strls);
		((t_minos*)(cur_elem->content))->index = i / 4;
		ft_lstappend(&tm_list, cur_elem);
		i += 4;
	}
	ft_strlsdel(&inputfile_strls);
	return (tm_list);
}
