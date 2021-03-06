/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 17:02:13 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 20:20:23 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			continue ;
		else
			break ;
	}
	if (str[i])
		return (0);
	else
		return (1);
}
