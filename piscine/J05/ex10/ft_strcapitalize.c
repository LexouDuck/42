/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:50:04 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/13 13:53:35 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	capitalize(char *c, int *state)
{
	if ('a' <= *c && *c <= 'z')
	{
		if (*state)
		{
			*c -= 'a';
			*c += 'A';
			*state = 0;
		}
	}
	else if ('A' <= *c && *c <= 'Z')
	{
		if (*state)
			*state = 0;
		else
		{
			*c -= 'A';
			*c += 'a';
		}
	}
	else
		*state = 1;
}

char	*ft_strcapitalize(char *str)
{
	int state;
	int i;

	i = 0;
	state = 1;
	while (str[i])
	{
		capitalize(str + i, &state);
		i++;
	}
	return (str);
}
