#!/bin/bash
folder=/tmp/gnl

rm -rf $folder
mkdir $folder
cp ~/Documents/04-get_next_line/auteur			$folder
cp ~/Documents/04-get_next_line/get_next_line.c	$folder
cp ~/Documents/04-get_next_line/get_next_line.h	$folder
mkdir $folder/libft
cp ~/Documents/02-libft/ft_*.c		$folder/libft
cp ~/Documents/02-libft/Makefile	$folder/libft
cp ~/Documents/02-libft/libft.h		$folder/libft
sh ~/42FileChecker/42FileChecker.sh
