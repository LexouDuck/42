/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:08:32 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 21:40:05 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>

# define OK 0
# define ERROR 1
# define BUFFER_SIZE 4096

typedef struct	s_chunk
{
	int				size;
	char			*str;
	struct s_chunk	*prev;
	struct s_chunk	*next;
}				t_chunk;

typedef struct	s_tiles
{
	char	free;
	char	obst;
	char	fill;
}				t_tiles;

typedef struct	s_square
{
	int		x;
	int		y;
	int		size;
	int		map_w;
	int		map_h;
	int		map_size;
	t_tiles	*tiles;
}				t_square;

int				ft_strlen(char *str);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strcat(char *dest, char *src);
char			*ft_strncat(char *dest, char *src, int nb);

void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_putnbr(int nb);

char			**split_map(char *str, char *charset);
int				is_separator(char c, char *charset);
int				count_words(char *str, char *charset);
int				count_letters(char *str, int ws, char *charset);

int				read_map(char *filepath);
char			**make_map(int fd, int *length, t_tiles *tiles, t_square *bsq);
t_chunk			*make_linked_list(int fd, int *length);
char			*concat_mapstr(t_chunk *llist, int length);

int				check_map(char **strls, t_tiles *charset, int *x, int *y);
int				check_tileset(char **strls, t_tiles *charset, int *height);
int				check_map_dim(char **strls, t_tiles *charset, int *x, int *y);
int				check_map_char(char **strls, t_tiles *charset, int x, int y);

int				solve(t_square *curr_sq, t_tiles *tiles, char **map);
char			**make_boolmap(t_tiles *tiles, char **map, int rows, int cols);
void			clean_boolmap(char **boolmap, t_square *bsq, int f_y, int f_x);
int				iterate_edges(char **map, t_square *bsq, char **boolmap);
t_square		rec_fill(int *pos, char **boolmap, char **map, t_square *bsq);

void			show_map(char **strls);
int				show_map_w_sq(char **map, t_square *bsq);

#endif
