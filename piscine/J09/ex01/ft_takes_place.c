/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_takes_place.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:46:26 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/07 18:34:42 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_takes_place(int hour);

void	ft_takes_place(int hour)
{
	int next;

	hour %= 24;
	if (hour == 12)
	{
		printf("THE FOLLOWING TAKES PLACE BETWEEN 12.00 P.M. AND 1.00 P.M.\n");
		return ;
	}
	if (hour == 0)
	{
		printf("THE FOLLOWING TAKES PLACE BETWEEN 12.00 A.M. AND 1.00 A.M.\n");
		return ;
	}
	next = hour + 1;
	printf("THE FOLLOWING TAKES PLACE BETWEEN %d.00 %s AND %d.00 %s\n",
			hour % 12, (hour < 12) ? "A.M." : "P.M.",
			next % 12, (next < 12) ? "A.M." : "P.M.");
}
