/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 17:10:35 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 20:20:53 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 32)
			continue ;
		else
			break ;
	}
	if (str[i])
		return (0);
	else
		return (1);
}
