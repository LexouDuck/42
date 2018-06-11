/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_matrix	*matrix_new(t_vector *u, t_vector *v, t_vector *w, t_vector *t)
{
	t_matrix	*result;

	if (!(result = (t_matrix *)malloc(sizeof(t_matrix))))
		return (NULL);
	result->u = u;
	result->v = v;
	result->w = w;
	result->t = t;
	return (result);
}

inline void	matrix_set(t_matrix *result, t_vector *u, t_vector *v, t_vector *w)
{
	result->u = u;
	result->v = v;
	result->w = w;
}

inline void	matrix_transpose(t_matrix *matrix)
{
	float tmp;

	tmp = matrix->u->y;
	matrix->u->y = matrix->v->x;
	matrix->v->x = tmp;
	tmp = matrix->v->z;
	matrix->v->z = matrix->w->y;
	matrix->w->y = tmp;
	tmp = matrix->u->z;
	matrix->u->z = matrix->w->x;
	matrix->w->x = tmp;
}

void		matrix_inverse(t_matrix *matrix)
{
	t_vector	*u;
	t_vector	*v;
	t_vector	*w;
	double		deter;

	u = vector_new(matrix->u->x, matrix->u->y, matrix->u->z);
	v = vector_new(matrix->v->x, matrix->v->y, matrix->v->z);
	w = vector_new(matrix->w->x, matrix->w->y, matrix->w->z);
	deter = u->x * (v->y * w->z - v->z * w->y) -
			u->y * (v->x * w->z - v->z * w->x) +
			u->z * (v->x * w->y - v->y * w->x);
	deter = 1 / deter;
	matrix->u->x = (v->y * w->z - w->y * v->z) * deter;
	matrix->u->y = (w->y * u->z - u->y * w->z) * deter;
	matrix->u->z = (u->y * v->z - v->y * u->z) * deter;
	matrix->v->x = (v->z * w->x - w->z * v->x) * deter;
	matrix->v->y = (w->z * u->x - u->z * w->x) * deter;
	matrix->v->z = (u->z * v->x - v->z * u->x) * deter;
	matrix->w->x = (v->x * w->y - w->x * v->y) * deter;
	matrix->w->y = (w->x * u->y - u->x * w->y) * deter;
	matrix->w->z = (u->x * v->y - v->x * u->y) * deter;
	free(u);
	free(v);
	free(w);
}

t_matrix	*matrix_multiply(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*result;
	t_vector	*vector;

	if (!(result = (t_matrix *)malloc(sizeof(t_matrix))))
		return (NULL);
	vector = m1->u;
	result->u = vector_new(
		vector->x * m2->u->x + vector->y * m2->v->x + vector->z * m2->w->x,
		vector->x * m2->u->y + vector->y * m2->v->y + vector->z * m2->w->y,
		vector->x * m2->u->z + vector->y * m2->v->z + vector->z * m2->w->z);
	vector = m1->v;
	result->v = vector_new(
		vector->x * m2->u->x + vector->y * m2->v->x + vector->z * m2->w->x,
		vector->x * m2->u->y + vector->y * m2->v->y + vector->z * m2->w->y,
		vector->x * m2->u->z + vector->y * m2->v->z + vector->z * m2->w->z);
	vector = m1->w;
	result->w = vector_new(
		vector->x * m2->u->x + vector->y * m2->v->x + vector->z * m2->w->x,
		vector->x * m2->u->y + vector->y * m2->v->y + vector->z * m2->w->y,
		vector->x * m2->u->z + vector->y * m2->v->z + vector->z * m2->w->z);
	return (result);
}
