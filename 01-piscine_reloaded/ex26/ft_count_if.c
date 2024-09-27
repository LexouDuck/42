/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:30:58 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 20:09:02 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char*))
{
	int result;
	int i;

	if (!tab || !*tab || !f)
		return (0);
	result = 0;
	i = 0;
	while (tab[i])
	{
		if (f(tab[i]) == 1)
			result++;
		i++;
	}
	return (result);
}
