/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 15:05:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/08 16:07:45 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		join_strlen1(char *str);

void	join_strlen2(char **str_ls, int *str_nb, int *char_nb);

void	join_str(char *str, char **str_ls, char *sep);

char	*ft_join(char **tab, char *sep)
{
	char	*str;
	int		strls_str_nb;
	int		strls_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

	join_strlen2(tab, &strls_str_nb, &strls_char_nb);
	total_sep_char_nb = (strls_str_nb - 1) * join_strlen1(sep);
	total_char_nb = total_sep_char_nb + strls_char_nb;
	str = (char*)malloc((total_char_nb + 1) * sizeof(*str));
	join_str(str, tab, sep);
	return (str);
}

void	join_str(char *str, char **str_ls, char *sep)
{
	int i;
	int dim1;
	int dim2;
	int sep_i;

	i = 0;
	sep_i = 0;
	dim1 = -1;
	while (str_ls[++dim1])
	{
		dim2 = 0;
		while (str_ls[dim1][dim2])
		{
			*(str + i) = str_ls[dim1][dim2];
			dim2++;
			i++;
		}
		sep_i = 0;
		while (sep[sep_i] && str_ls[dim1 + 1])
		{
			*(str + i) = sep[sep_i++];
			i++;
		}
	}
	*(str + i) = '\0';
}

void	join_strlen2(char **str_ls, int *str_nb, int *char_nb)
{
	int str_at;
	int len;

	len = 0;
	str_at = 0;
	while (str_ls[str_at])
	{
		*(char_nb) += join_strlen1(str_ls[str_at]);
		str_at++;
	}
	*str_nb = str_at;
}

int		join_strlen1(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
