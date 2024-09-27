/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

#define SHAPE_AMOUNT	5

void	rtv1_printdebug(t_rtv1 *rtv1)
{
	t_object *object;
	t_light *light;
	t_list *lst;
	int	type;

	ft_output_line("RTV1 File parsed:");
	ft_output_str("- Background color: ");
	ft_output_str("#");
	ft_output_line(ft_u32_to_hex(rtv1->bg_color));
	ft_output_line("- Lights:");
	lst = rtv1->lights;
	while (lst)
	{
		light = (t_light *)lst->item;
		if (light == NULL)
		{
			lst = lst->next;
			continue;
		}
		ft_output_str("\t#");
		ft_output_str(ft_u32_to_hex(light->color));
		ft_output_str(", ");
		ft_output_str(ft_f32_to_str(light->strength, 6));
		ft_output_str(", (");
		ft_output_str(ft_f32_to_str(light->position.x, 3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(light->position.y, 3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(light->position.z, 3)); ft_output_str(")\n");
		lst = lst->next;
	}
	ft_output_line("- Objects:");
	lst = rtv1->objects;
	while (lst)
	{
		object = (t_object *)lst->item;
		if (object == NULL)
		{
			lst = lst->next;
			continue;
		}
		static const char *types[SHAPE_AMOUNT] =
		{
			"N/A ",
			"SPHERE   ",
			"CYLINDER ",
			"CUBE     ",
			"CONE     ",
		};
		type = (int)object->type;
		if (type >= SHAPE_AMOUNT)
			type = 0;
		ft_output_str("\t");
		ft_output_str(types[type]);
		ft_output_str("-> #");
		ft_output_str(ft_u32_to_hex(object->color));         ft_output_str(",\t(");
		ft_output_str(ft_f32_to_str(object->position.x, 3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(object->position.y, 3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(object->position.z, 3)); ft_output_str(")\t{");
		ft_output_str(ft_f32_to_str(object->rotation.x, 3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(object->rotation.y, 3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(object->rotation.z, 3)); ft_output_str("}\t[");
		ft_output_str(ft_f32_to_str(object->scale.x,    3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(object->scale.y,    3)); ft_output_str(", ");
		ft_output_str(ft_f32_to_str(object->scale.z,    3)); ft_output_str("]\n");
		lst = lst->next;
	}
}
