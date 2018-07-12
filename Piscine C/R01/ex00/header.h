/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 19:22:55 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/10 19:30:50 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

int		setup(int sudoku[9][9], char **argv);

void	display(int sudoku[9][9]);

int		is_solved(int sudoku[9][9]);

int		resolve(int sudoku[9][9]);

void	resolve_row(int sudoku[9][9], int y, int possible[9]);
void	resolve_column(int sudoku[9][9], int x, int possible[9]);
void	resolve_square(int sudoku[9][9], int x, int y, int possible[9]);

int		resolve_possibilities(int sudoku[9][9], int x, int y, int possible[9]);

#endif
