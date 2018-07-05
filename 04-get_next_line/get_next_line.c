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

#include "get_next_line.h"

static	void	gnl_delete_elem(void *content, size_t fd)
{
	free(content);
	if (fd)
		return ;
}

static	void	gnl_delete_listelem(t_list **store, int fd, char **line)
{
	t_list	*lst;
	t_list	*result;

	*line = NULL;
	result = NULL;
	lst = *store;
	while (lst)
	{
		if (lst->next && (int)lst->next->content_size == fd)
		{
			result = lst->next;
			lst->next = result->next;
			break;
		}
		lst = lst->next;
	}
	if (result)
		ft_lstdelone(&result, &gnl_delete_elem);
}

static	int		gnl_read_file(t_list *elem)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;

	ft_bzero(buffer, BUFF_SIZE + 1);
	while (!ft_strchr(elem->content, '\n') &&
		(result = read((int)elem->content_size, buffer, BUFF_SIZE)) > 0)
	{
		temp = (char *)elem->content;
		if (!(elem->content = ft_strjoin(temp, buffer)))
			return (0);
		free(temp);
	}
	if (result == 0 && buffer[result] == '\0')
		return (-2147483648);
	return (result);
}

static	int		gnl_make_line(t_list *elem, char **line)
{
	int		space;
	char	*str;

	space = 0;
	str = elem->content;
	while (str[space])
	{
		if (str[space] == '\n')
			break ;
		++space;
	}
	str = NULL;
	*line = ft_strsub(elem->content, 0, space);
	if (!(str = (char *)malloc(sizeof(str) * (ft_strlen(elem->content) + 1))))
		return (GNL_ERROR);
	ft_strcpy(str, (char *)elem->content + space + 1);
	ft_strclr(elem->content);
	elem->content = ft_strcpy(elem->content, str);
	free(str);
	return (GNL_LINE);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*store = NULL;
	t_list			*elem;
	int				result;

	if (line == NULL || BUFF_SIZE < 0 || fd < 0)
		return (GNL_ERROR);
	if (!store && !(store = ft_lstnew(NULL, fd)))
		return (GNL_ERROR);
	elem = store;
	while (elem && (int)elem->content_size != fd)
		elem = elem->next;
	if (!elem)
		ft_lstappend(&store, (elem = ft_lstnew(NULL, fd)));
	if (!elem->content && !(elem->content = ft_strnew(2)))
		return (GNL_ERROR);
	if ((result = gnl_read_file(elem)) < 0)
		return (result == -2147483648 ? GNL_END : GNL_ERROR);
	if (*(char *)elem->content == '\0')
	{
		gnl_delete_listelem(&store, fd, line);
		return (GNL_END);
	}
	if (gnl_make_line(elem, line) < 0)
		return (GNL_ERROR);
	return (GNL_LINE);
}
/*
**	ft_putstr("content: ");
**	ft_putstr(ft_itoa_hex((t_u64)elem->content, "0x"));
**	ft_putstr(" -> {");
**	ft_putstr((char *)elem->content);
**	ft_putstr("}, fd: ");
**	ft_putendl(ft_itoa((int)elem->content_size));
*/
