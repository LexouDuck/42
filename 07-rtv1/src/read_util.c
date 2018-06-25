/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		read_whitespace(t_parser *parser)
{
	char	*file;

	file = parser->file;
	while (file[parser->index] &&
		(ft_isspace(file[parser->index]) || file[parser->index] == '/'))
	{
		if (file[parser->index] == '\n')
			++(parser->line);
		else if (file[parser->index] == '/' && file[parser->index + 1] == '/')
		{
			while (file[parser->index] && file[parser->index] != '\n')
				++(parser->index);
			++(parser->line);
		}
		++(parser->index);
	}
}

static char	*read_vector_arg_number(t_parser *parser, float *result, char sep)
{
	char	*file;
	char	*number;

	read_whitespace(parser);
	file = parser->file;
	number = file + parser->index;
	while (file[parser->index] &&
		(ft_isdigit(file[parser->index]) ||
			file[parser->index] == '+' ||
			file[parser->index] == '-' ||
			file[parser->index] == '.'))
		++(parser->index);
	if (!file[parser->index])
		return ("Unexpected end of file inside vector argument");
	read_whitespace(parser);
	if (file[parser->index] != sep)
		return (ft_strrep_char(ft_strrep_char(
			"Expected '@' separator char, but read: '_'", '@', sep),
			'_', file[parser->index]));
	file[parser->index] = '\0';
	++(parser->index);
	*result = ft_atof(number);
	return (NULL);
}

char		*read_vector_arg(t_parser *parser, t_vector *result)
{
	char	*error;
	char	symbol;

	read_whitespace(parser);
	if (!parser->file[parser->index])
		return ("Expected vector argument, reached end of file");
	symbol = parser->file[parser->index];
	if (symbol == '(' || symbol == '{' || symbol == '[')
		++(parser->index);
	else
		return (ft_strrep_char(
		"Expected vector arg '(', '{' or '[', but read: '_'", '_', symbol));
	symbol += (symbol == '(') ? 1 : 2;
	if ((error = read_vector_arg_number(parser, &(result->x), ',')))
		return (error);
	if ((error = read_vector_arg_number(parser, &(result->y), ',')))
		return (error);
	if ((error = read_vector_arg_number(parser, &(result->z), symbol)))
		return (error);
	return (NULL);
}

char		*read_number_arg(t_parser *parser, float *result)
{
	char	c;
	char	*file;
	char	*number;

	read_whitespace(parser);
	file = parser->file;
	c = file[parser->index];
	if (c == '\0')
		return ("Expected number argument, reached end of file");
	else if (ft_isdigit(c))
	{
		number = file + parser->index;
		while (file[parser->index] &&
			(ft_isdigit(file[parser->index]) || file[parser->index] == '.'))
			++(parser->index);
		if (file[parser->index] == '\n')
			parser->line += 1;
		file[parser->index] = '\0';
		++(parser->index);
		*result = ft_atof(number);
		return (NULL);
	}
	else
		return (ft_strrep_char(
		"Expected number argument digit, but read: '_'", '_', c));
}

char		*read_color_arg(t_parser *parser, t_u32 *result)
{
	char	c;
	char	*file;
	char	*color;

	read_whitespace(parser);
	file = parser->file;
	c = file[parser->index];
	if (c == '\0')
		return ("Expected color argument, reached end of file");
	else if (c == '#')
	{
		++(parser->index);
		color = file + parser->index;
		while ((c = file[parser->index]) && (ft_isdigit(c) ||
			('A' <= c && c <= 'F') || ('a' <= c && c <= 'f')))
			++(parser->index);
		if (file[parser->index] == '\n')
			parser->line += 1;
		file[parser->index] = '\0';
		++(parser->index);
		*result = ft_atoi_hex(color);
		return (NULL);
	}
	else
		return (ft_strrep_char(
		"Expected '#' char for color arg, but read: '_'", '_', c));
}
