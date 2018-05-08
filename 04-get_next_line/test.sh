#!/bin/bash

rm -rf /tmp/gnl
cp -rf ~/Documents/04-get_next_line /tmp/gnl
rm -rf /tmp/gnl/libft
cp -rf ~/Documents/02-libft /tmp/gnl/libft
rm -rf /tmp/gnl/get_next_line.old.c
rm -rf /tmp/gnl/main*
rm -rf /tmp/gnl/test.sh
rm -rf /tmp/gnl/sujet.pdf
rm -rf /tmp/gnl/libft/main*
rm -rf /tmp/gnl/libft/test.sh
rm -rf /tmp/gnl/libft/sujet.pdf
sh ~/42FileChecker/42FileChecker.sh
