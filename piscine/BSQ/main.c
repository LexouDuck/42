/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:54:38 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 20:19:03 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		main(int argc, char **argv)
{
	int i;

	if (argc <= 1)
	{
		if (read_map("stdin"))
			write(2, "map error\n", 10);
	}
	else
	{
		i = 0;
		while (++i < argc)
		{
			if (read_map(argv[i]))
				write(2, "map error\n", 10);
		}
	}
	return (OK);
}
