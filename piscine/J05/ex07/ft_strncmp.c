/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:18:55 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 20:19:24 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
		{
			c1 = s1[i];
			c2 = s2[i];
			return (c1 - c2);
		}
		i++;
	}
	return (0);
}
