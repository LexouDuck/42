/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 17:10:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 20:20:44 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ('A' <= str[i] && str[i] <= 'Z')
			continue ;
		else
			break ;
	}
	if (str[i])
		return (0);
	else
		return (1);
}
