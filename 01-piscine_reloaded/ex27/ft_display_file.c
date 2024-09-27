/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:07:25 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 20:09:23 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	write_file(int file_desc)
{
	char	buffer[BUFFER_SIZE + 1];
	int		length;

	if (file_desc == -1)
		return (ERROR);
	buffer[BUFFER_SIZE] = '\0';
	while ((length = read(file_desc, buffer, BUFFER_SIZE)))
	{
		write(1, buffer, length);
	}
	return (OK);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		write(2, "File name missing.\n", 19);
		return (ERROR);
	}
	else if (argc == 2)
	{
		return (write_file(open(argv[1], O_RDONLY)));
	}
	else
	{
		write(2, "Too many arguments.\n", 20);
		return (ERROR);
	}
}
