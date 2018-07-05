/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 10:13:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/26 07:19:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../get_next_line.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define DEBUG_PRINTF if (GNLDEBUG) printf


int         ref_myputnchar(char *str, int num);

#define CALL_GNL(ret, fd, line) \
DEBUG_PRINTF("Calling fd(%2d)... \n", fd);\
fflush(stdout);\
ret = get_next_line(fd, line);\
DEBUG_PRINTF("Done.\n");\
printf("Ret (%2d) *line(%s)\n", ret, *line);\
DEBUG_PRINTF(" \n\n");\
fflush(stdout);



int		is_tocall_left(int tab[20])
{
	int j;

	for (j = 0; j < 20; j++)
	{
		if (tab[j] > 0)
			return (1);
	}
	return (0);
}

int		do_my_tests(void)
{
#define RANDOM 0 //0 ou 1
#define NUMLOOP 1 //1 ou plus
#define NUMPOSTCALLS 2 //0 ou plus
#define DOUNTIL 20 //nb de tests/files

char *files[DOUNTIL];
	files[0] = "t0.txt"; // 'salut\n'
	files[1] = "t1.txt"; // rien
	files[2] = "t2.txt"; // '/n'
	files[3] = "t3.txt"; // 2 'M\n'
	files[4] = "t4.txt"; // 2 char '\0\n'
	files[5] = "t5.txt"; // 2 char '\n\n'
	files[6] = "t6.txt"; // '01234\n'
	files[7] = "t7.txt"; // \n\n\n01234\n  
	files[8] = "t8.txt"; // 01234\n\n\n
	files[9] = "t9.txt"; // \n\n01234\n\nabcde\n
	files[10] = "t10.txt"; //header 42 
	files[11] = "t11.txt"; // 
	files[12] = "t12.txt"; // 
	files[13] = "t13.txt"; // 
	files[14] = "t10.txt"; // 
	files[15] = "t15.txt"; // 
	files[16] = "t16.txt"; // 
	files[17] = "t17.txt"; // 
	files[18] = "t18.txt"; // 
	files[19] = "t19.txt"; // 

/*

2x gestion \0
1x free
1x protection mallocs

*/
	
	int gnlret;
	char *gnlstr;

	int fd[DOUNTIL];
	int ret[DOUNTIL];
	int i;

	int tocall[DOUNTIL];
	int j;

	int post = NUMPOSTCALLS;
	(void)post;


	for (i = 0; i < DOUNTIL; i++)
	{
		fd[i] = open(files[i], O_RDONLY);
		if (fd[i] > 0)
			printf("openned[%s](%d)  ", files[i], fd[i]);
		else
			printf("couldnt open [%s](%d)  ", files[i], fd[i]);
		printf("\n");
	}
	printf("\n");


#if RANDOM == 0 // DONT TOUCH
	for (i = 0; i < DOUNTIL; i++)
	{
		printf("\n");
		/* if (fd[i] < 0) */
			/* continue ; */

		post = NUMPOSTCALLS;
		do
		{
			printf("%2d%7s Call:",
				   fd[i], files[i]);
			fflush(stdout);

			gnlret = get_next_line(fd[i], &gnlstr);
			printf("(%d)[len%2zu]{",
				  gnlret, gnlstr ? strlen(gnlstr) : 0);
			fflush(stdout);
			if (gnlstr == NULL)
				printf("GNLSTR:NULL");
			else
				ref_myputnchar(gnlstr, 100);
			printf("}");			fflush(stdout);

			if (gnlret > 0)
			{
				printf("freeing:");            fflush(stdout);
				free(gnlstr);
			}
			else
				printf("NOT freeing:");
			printf("\n");			fflush(stdout);
			if (gnlret > 0)
				post = NUMPOSTCALLS;
		}
		while (gnlret > 0 || post-- > 0);
		
	}

#else // ELSE RANDOM
	j = 0;
	for (j = 0; j < 20 ; j++)
		tocall[j] = -15;

	printf("CALL 01 ========================================\n");
	for (i = 0; i < DOUNTIL; i++)
	{
		if (fd[i] < 0)
			continue ;
		gnlret = get_next_line(fd[i], &gnlstr);		
printf("%2d%7s(%d)[len%2zu]{", fd[i], files[i], gnlret, strlen(gnlstr));
			fflush(stdout);
			ref_myputnchar(gnlstr, 50);
			printf("}\n");



		tocall[i] = gnlret;
	}
	int k = 2;
	while (is_tocall_left(tocall))
	{
		printf("CALL %02d ========================================\n", k++);
		for (i = 0; i < DOUNTIL; i++)
		{
			if (tocall[i] <= 0)
				continue ;
		gnlret = get_next_line(fd[i], &gnlstr);		
			printf("%2d%7s(%d)[len%2zu]{", fd[i], files[i], gnlret, strlen(gnlstr));
			fflush(stdout);
			ref_myputnchar(gnlstr, 50);
			printf("}\n");


		tocall[i] = gnlret;
			
		}
		
	}
	
#endif
	for (i = 0; i < DOUNTIL; i++)
	{
		j = close(fd[i]);
		printf("closed[%s](%d){ret:%d}  ", files[i], fd[i], j);
	}
	printf("\n");


	(void)ret;
	(void)j;
	(void)tocall;
	ft_putstr("GNL test end\n");
	return (0);
}

static void putbs(char c, int *count)
{
    ft_putstr("\033[33m");
	if (c == 0)
		printf("0");
	else
		printf("?");
	fflush(stdout);
    ft_putstr("\033[39m");

    if (c < 0)
        (*count)++;
    if (c <= -10 || c >= 10)
        (*count)++;
    if (c <= -100 || c >= 100)
        (*count)++;
}


int         ref_myputnchar(char *str, int num)
{
    int count;

    if (!str)
    {
        ft_putstr("\033[33m(null)\033[39m");
        return (6);
    }
    count = 0;
    while (num > 0)
    {
        if (isprint(*str))
		{printf("%c", *str); fflush(stdout);}
        else
            putbs(*str, &count);
        str++;
        num--;
        count++;
    }
    return (count);
}


int		main(void)
{
	int i;

	for (i = 0; i < NUMLOOP ; i++)
		do_my_tests();

	(void)i;
/* 	while (1) */
/* 		; */
	return (0);
}
