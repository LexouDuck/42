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

static char	*rtv1_read_object(t_rtv1 *rtv1, t_parser *parser, t_geom shape)
{
	char		*error;
	t_object	*object;

	if (!(object = (t_object *)malloc(sizeof(t_object))))
		return ("Couldn't create 3D object");
	object->type = shape;
	if ((error = read_color_arg(parser, &(object->color))))
		return (error);
	if ((error = read_vector_arg(parser, &(object->position))))
		return (error);
	if ((error = read_vector_arg(parser, &(object->rotation))))
		return (error);
	if ((error = read_vector_arg(parser, &(object->scale))))
		return (error);
	ft_lstadd(&(rtv1->objects), ft_lstnew(object, sizeof(t_object)));
	return (NULL);
}

static char	*rtv1_read_light(t_rtv1 *rtv1, t_parser *parser)
{
	char		*error;
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return ("Couldn't create 3D light");
	if ((error = read_color_arg(parser, &(light->color))))
		return (error);
	if ((error = read_number_arg(parser, &(light->strength))))
		return (error);
	if ((error = read_vector_arg(parser, &(light->position))))
		return (error);
	ft_lstadd(&(rtv1->lights), ft_lstnew(light, sizeof(t_light)));
	return (NULL);
}

static char	*rtv1_read_bgcolor(t_rtv1 *rtv1, t_parser *parser)
{
	char	*error;

	if ((error = read_color_arg(parser, &(rtv1->bg_color))))
		return (error);
	return (NULL);
}

static char	*rtv1_read_command(t_rtv1 *rtv1, t_parser *parser, char *label)
{
	t_geom	shape;

	shape = none;
	if (ft_strequ(label, "NONE"))
		return ("'NONE' is not a valid usable label.");
	else if (ft_strequ(label, "PLANE"))
		shape = plane;
	else if (ft_strequ(label, "TRIANGLE"))
		shape = triangle;
	else if (ft_strequ(label, "SPHERE"))
		shape = sphere;
	else if (ft_strequ(label, "CYLINDER"))
		shape = cylinder;
	else if (ft_strequ(label, "CONE"))
		shape = cone;
	if (shape != none)
		return (rtv1_read_object(rtv1, parser, shape));
	else if (ft_strequ(label, "LIGHT"))
		return (rtv1_read_light(rtv1, parser));
	else if (ft_strequ(label, "BG"))
		return (rtv1_read_bgcolor(rtv1, parser));
	else
		return (ft_strjoin("Could not resolve label -> ", label));
}

char		*rtv1_read_file(t_rtv1 *rtv1, t_parser *parser, int fd)
{
	char	*label;
	char	*error;

	parser->line = 1;
	parser->file = NULL;
	if (read_file(fd, &(parser->file)))
		return ("Couldn't read rt file");
	parser->index = 0;
	while (parser->file[parser->index])
	{
		read_whitespace(parser);
		if (!parser->file[parser->index])
			break ;
		label = parser->file + parser->index;
		while (parser->file[parser->index] &&
			ft_isalpha(parser->file[parser->index]))
			++(parser->index);
		if (!parser->file[parser->index])
			return ("Unexpected end of file after label");
		parser->file[parser->index++] = '\0';
		if ((error = rtv1_read_command(rtv1, parser, label)))
			return (error);
	}
	free(parser->file);
	return (NULL);
}
