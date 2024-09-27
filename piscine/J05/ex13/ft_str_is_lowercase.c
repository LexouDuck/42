/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 17:09:53 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 20:20:33 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ('a' <= str[i] && str[i] <= 'z')
			continue ;
		else
			break ;
	}
	if (str[i])
		return (0);
	else
		return (1);
}
