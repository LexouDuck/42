/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:07:47 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 20:42:02 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FILLIT_H
# define __FILLIT_H

# include "./libft/libft.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

/*
** Replaced with stdlib EXIT_SUCCESS and EXIT_FAILURE macros
** # define OK 0
** # define ERROR 1
*/

/*
** Since 26 pieces is max, and input file format is restrictive
** (4*4 squares (+1 on each line for \n), each separated by a single
** newline, plus EOF. Any file larger than 26*4*(4+1)+25+1 = 546 is
** necessarily incorrect. So buffersize is useless, we replace it
** with MAX_FILE_SIZE.
*/
# define MAX_VALID_FILE_SIZE 546

/*
** Tile type number, not counting "EMPTY" tile.
*/
# define DIFF_PIECE_NB 19

/*
** TMINOS nomenclature; all rotations are clockwise
**
**	##		=>		Square
**	##
**
**
**
**	####	=>		line_hrz
**
**	#
**	#
**	#		=>		line_vrt
**	#
**
**
**
**	 ##
**	##		=>		S_hrz
**
**	#
**	##		=>		S_vrt
**	 #
**
**
**	##
**	 ##		=>		Z_hrz
**
**	 #
**	##		=>		Z_vrt
**	#
**
**
**	#
**	#		=>		Lnrm_rot0
**	##
**
**	###
**	#		=>		Lnrm_rot90
**
**
**	##
**	 #		=>		Lnrm_rot180
**	 #
**
**	  #
**	###		=>		Lnrm_rot270
**
**
**
**	 #
**	 #		=>		Lrev_rot0
**	##
**
**	#
**	###		=>		Lrev_rot90
**
**
**	 ##
**	 #		=>		Lrev_rot180
**	 #
**
**	###
**	  #		=>		Lrev_rot270
**
**
**
**
**	###		=>		T_rot0
**	 #
**
**	  #
**	 ##		=>		T_rot90
**	  #
**
**	 #
**	###		=>		T_rot180
**
**
**	#
**	##		=>		T_rot270
**	#
*/

/*
** Enum for all different tm types.
** EMPTY tile serves for debugging.
** All rotations are clockwise, as can be inferred from above.
*/
typedef enum	e_tmtype
{
	square,
	line_hrz,
	line_vrt,
	s_hrz,
	s_vrt,
	z_hrz,
	z_vrt,
	l_nrm_rot0,
	l_nrm_rot90,
	l_nrm_rot180,
	l_nrm_rot270,
	l_rev_rot0,
	l_rev_rot90,
	l_rev_rot180,
	l_rev_rot270,
	t_rot0,
	t_rot90,
	t_rot180,
	t_rot270,
	EMPTY
}				t_tmtype;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

/*
** Tetraminos struct :
** - type :		tetraminos piece type (explained above)
** - size :		tetramino dimensions as an (x,y) vector
** - pos :		tetramino position as an (x,y) point on
**				  sq->layout corresponding to tm's (0,0).
**				  //TODO: Use in solver.
** - layout:	the tetramino's representation as a strls
** - index :	index of tm in the tm_list.
*/
typedef struct	s_minos
{
	t_tmtype	type;
	t_point		size;
	t_point		pos;
	char const	**layout;
	t_u8		index;
}				t_minos;

/*
** Square struct :
** - size :			dimension of square solution grid.
** - sizexsize :	the size of this square, squared :D
** - layout :		current version of the "solution" being built.
** - tm_list :		list of all tm-s that need to fit into a single square.
** - tmlst_size :	size of tm_list to recognize when a solution is found.
*/
typedef struct	s_square
{
	int			size;
	int			sizexsize;
	char		**layout;
	t_list		*tm_list;
	t_u8		tmlst_size;
}				t_square;

/*
** ----------------------
*/
/*
**		main.c
*/

/*
** Exits the process sending msg to stderr. If the empty string
** is used as input, sends the 42-required "error\n" to stderr.
*/
void			exit_error(char const *msg);
/*
** Functions to display data for debugging purposes.
** These functions should be removed in the final build.
*/
void			display_tm(t_minos *tm);
void			display_tm_lstelem(t_list *tm_lstelem);
void			display_tm_list(t_list *tm_list);
/*
** Two steps: one, check the input and if valid make an abstract
** representation of the problem as an indexed list of t_minos.
** Two, run the solve function on the list. The solve function
** returns void and should print the result when it finds it.
*/
int				main(int argc, char **argv);

/*
** ----------------------
*/
/*
**		reader.c
*/

/*
** Reads the file given in input, checking for correctness as specified.
** Returns a list of "abstract" t_minos to be used in 'solve()'.
**
** 		--subcall:
** static void	check_input_file(char const *filedata);
*/
t_list			*read_fillit_file(char const *filepath);

/*
** ----------------------
*/
/*
**		solver.c
*/

/*
** Picks bigger and bigger squares to run recursive backtracking
** on for the sequence of pieces available.
** 		--subcalls:
**	static int 	recursive(t_square *sq, t_u8 index);
**	static int	sqrt_rounded_down(int nb);
*/
void			solve(t_list *tm_list);

/*
** ----------------------
*/
/*
**		util_t_minos.c
*/

/*
** Returns a list of "abstract" t_minos from filedata.
** Checks for format validity, and exits if invalid or
** if any other error is encountered.
**
** 		--subcalls :
** static void		verify_tminos(char const **tm_4by4);
** static int		count_adjacencies(char const **tm_4by4, int y, int x);
** static t_minos	*new_tminos(char const **tm_4by4);
*/
t_list			*new_lst_tminos(char const *a_filedata);

/*
** ----------------------
*/
/*
**		util_t_square.c //TODO THIS SECTION MIGHT NEED DEBUGGING
*/

/*
** Returns a newly allocated, defined square.
*/
t_square		*new_square(int size, t_list *tm_list);
/*
** Deletes a t_square and frees proper variables. Does not delete tm_list.
*/
void			del_square(t_square **sq);
/*
** Reads tm to update sq_layout with tm in the appropriate position.
** Checks for incoherent output before acting by calling "overlap" of
** map_utils.
*/
int				add_tm_to_sq_layout(t_minos const tm, t_square *sq);
/*
** Cleans sq's layout from all chars that are >= index (with 'A' being 0).
** Used when returning from a given branch that has failed in rec_backtrack.
*/
void			rebuild_layout(t_square *sq, t_u8 index);
/*
** Printable format of some relevant t_square attributes. Non-relevant are
** lengthy attributes that should be displayed independently.
** This function should be removed from the final build.
*/
void			display_square(t_square *sq);

/*
** ----------------------
*/
/*
**		util_map.c
*/

/*
** Creates a point on the stack.
*/
t_point			ft_newpoint(int y, int x);
/*
** Returns (0 <= y < map_y && 0 <= x < map_x)
*/
int				pt_in_bounds(int map_y, int map_x, int y, int x);
/*
** Returns a point to -1, -1 coordinates for instanciation and debug.
*/
void			ft_clrpoint(t_point *pt);
/*
** Returns true if any conflict should arise when inserting tm into sq.
** This includes boundary checks and superposition checks.
** Used in various parts of the code (reader and solver).
*/
int				overlap(t_minos const tm, t_square const sq);
/*
** Returns 1 if part overlaps nicely somewher in whole, 0 otherwise.
*/
int				str_2d_match(
					char const **part,
					char const **whole,
					t_point dim_p,
					t_point dim_w);

/*
** ----------------------
*/
/*
**		tmtype_to_strls.c
*/

/*
** Returns a char** layout of a piece from an t_tmtype.
** TODO: fix subcalls, make them shorter, using Tristan's ft_strdivide ?
*/
char			**tmtype_to_strls(t_tmtype type);

#endif
