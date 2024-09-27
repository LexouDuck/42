/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_vertex	*add_vertex(t_space *space, float x, float y, float z)
{
	t_vertex	*vertex;
	t_list		*result;

	if (!(vertex = (t_vertex *)malloc(sizeof(t_vertex))))
		return (NULL);
	vector_set(&vertex->absolute, x, y, z);
	vector_set(&vertex->projected, 0, 0, 0);
	vertex->display = (z <= 0 ? 0xFF : 0);
	vertex->display |= (((0xFF - (int)fabsf(z * 10)) & 0xFF) << 8);
	if (z > 0)
		vertex->display |= (((int)fabsf(z * 10) & 0xFF) << 16);
	if (!(result = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	result->item_size = sizeof(t_vertex);
	result->item = vertex;
	result->next = NULL;
	ft_lstadd(&(space->vertices), result);
	return (vertex);
}

t_edge		*add_edge(t_space *space, t_vertex *v1, t_vertex *v2)
{
	t_edge	*edge;
	t_list	*result;

	if (v1 == NULL || v2 == NULL || v1 == v2)
		return (NULL);
	if (!(edge = (t_edge *)malloc(sizeof(t_edge))))
		return (NULL);
	edge->vertex1 = v1;
	edge->vertex2 = v2;
	if (!(result = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	result->item_size = sizeof(t_edge);
	result->item = edge;
	result->next = NULL;
	ft_lstadd(&(space->edges), result);
	return (edge);
}

t_face		*add_face(t_space *space, t_edge *e1, t_edge *e2, t_edge *e3)
{
	t_face	*face;
	t_list	*result;

	if (e1 == NULL || e1 == e2 ||
		e2 == NULL || e2 == e3 ||
		e3 == NULL || e3 == e1)
		return (NULL);
	if (!(face = (t_face *)malloc(sizeof(t_face))))
		return (NULL);
	face->edge1 = e1;
	face->edge2 = e2;
	face->edge3 = e3;
	if (!(result = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	result->item_size = sizeof(t_face);
	result->item = face;
	result->next = NULL;
	ft_lstadd(&(space->faces), result);
	return (face);
}
