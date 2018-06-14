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

#include "../rtv1.h"

/*
**static void	rtv1_readmap_freelist(void *content, size_t content_size)
**{
**	if (content && content_size)
**		free(content);
**}
*/

static int	rtv1_readmap_line(t_list **file, char *line)
{
	char	*result;
	int		index;
	int		i;
	int		x;

	if (!(result = (char *)malloc(ft_strlen(line) / 2 + 2)))
		return (-1);
	i = 0;
	x = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			++i;
		index = i;
		if (line[i] == '-')
			++i;
		while (line[i] && ft_isdigit(line[i]))
			++i;
		if (line[i] == '\0' || index == i)
			break ;
		line[i++] = '\0';
		result[x++] = (char)ft_atoi(line + index);
	}
	ft_lstappend(file, ft_lstnew(result, x));
	return (x);
}

/*
** ft_putstr(  "x:"); ft_putstr(ft_strpad_l(ft_itoa(x), ' ', 4));
** ft_putstr(", y:"); ft_putstr(ft_strpad_l(ft_itoa(y), ' ', 4));
** ft_putstr(  " |"); ft_putendl(line);
*/

int			rtv1_readmap(t_rtv1 *rtv1, int fd)
{
	t_list	*file;
	int		result;
	char	*line;
	int		x;
	int		y;

	x = -1;
	y = 0;
	file = NULL;
	line = NULL;
	while ((result = get_next_line(fd, &line)) == 1)
	{
		if (x == -1)
			x = rtv1_readmap_line(&file, line);
		else if ((x = rtv1_readmap_line(&file, line)) == -1)
			return (ERROR);
		free(line);
		++y;
	}
	if (result < 0 || !(rtv1->map = (char **)ft_array(&file)))
		return (ERROR);
//ft_lstdel(&file, rtv1_readmap_freelist);
	rtv1->map_width = x;
	rtv1->map_height = y;
	return (OK);
}
