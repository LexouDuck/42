/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_vertex	*get_vertex(t_space *space, float x, float y, float z)
{
	t_vertex	*vertex;
	t_list		*lst;

	lst = space->vertices;
	while (lst)
	{
		if (lst->item == NULL)
			continue ;
		vertex = (t_vertex *)lst->item;
		if (vertex &&
			vertex->absolute.x == x &&
			vertex->absolute.y == y &&
			vertex->absolute.z == z)
			return (vertex);
		lst = lst->next;
	}
	return (NULL);
}

t_edge		*get_edge(t_space *space, t_vertex *v1, t_vertex *v2)
{
	t_edge	*edge;
	t_list	*lst;

	lst = space->edges;
	while (lst)
	{
		if (lst->item == NULL)
			continue ;
		edge = (t_edge *)lst->item;
		if (edge->vertex1 == v1 &&
			edge->vertex2 == v2)
			return (edge);
		lst = lst->next;
	}
	return (NULL);
}

t_face		*get_face(t_space *space, t_edge *e1, t_edge *e2, t_edge *e3)
{
	t_face	*face;
	t_list	*lst;

	lst = space->faces;
	while (lst)
	{
		if (lst->item == NULL)
			continue ;
		face = (t_face *)lst->item;
		if (face->edge1 == e1 &&
			face->edge2 == e2 &&
			face->edge3 == e3)
			return (face);
		lst = lst->next;
	}
	return (NULL);
}
