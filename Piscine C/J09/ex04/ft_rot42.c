/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot42.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 20:48:44 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/08 11:01:14 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_rot42(char *str);

int		rot42(int c, int basis)
{
	return ((((c - basis) + 42) % 26) + basis);
}

char	*ft_rot42(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		if ('a' <= str[i] && str[i] <= 'z')
		{
			str[i] = rot42(str[i], 'a');
		}
		if ('A' <= str[i] && str[i] <= 'Z')
		{
			str[i] = rot42(str[i], 'A');
		}
		i++;
	}
	return (str);
}
