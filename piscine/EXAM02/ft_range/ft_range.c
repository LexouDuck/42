/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 19:08:27 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 19:44:37 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int *ft_range(int start, int end)
{
	int length;
	int *result;
	int i = 0;

	if (start == end)
	{
		result = malloc(1);
		*result = start;
	}
	else if (start < end)
	{
		length = 1 + end - start;
		result = malloc(length * sizeof(int));
		while (start <= end)
		{
			result[i++] = start++;
		}
	}
	else
	{
		length = 1 + start - end;
		result = malloc(length * sizeof(int));
		while (end <= start)
		{
			result[i++] = start--;
		}
	}
	return (result);
}
