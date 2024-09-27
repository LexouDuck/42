/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 20:56:49 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 21:23:16 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void recursive(struct s_list *list, void *data_ref, int (*cmp)())
{
	if (!cmp(list->data, data_ref))
	{
		if (list->next && list->next->next)
		{
			free(list->next);
			list->next = list->next->next;
			return (recursive(list->next, data_ref, cmp));
		}
		else list->next = 0;
	}
	else return;
}

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	recursive(*begin_list, data_ref, cmp);
}
