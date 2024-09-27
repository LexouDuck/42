#include <unistd.h>
#include <string.h>
 
int     ft_putchar(char c)
{
    write(1, &c, 1);
    return (0);
}
 
void    ft_putnbr(int nb)
{
    int digits[50];
    int i;
    int order;
 
    if (nb < 0)
    {
        nb *= -1;
        ft_putchar('-');
    }
    if (nb == 0)
    {
        ft_putchar('0');
        return ;
    }
    i = 0;
    while (nb != 0)
    {
        digits[i++] = nb % 10;
        nb = nb / 10;
    }
    order = i;
    i = 0;
    while (i < order)
        ft_putchar(digits[order - 1 - i++] + 48);
}
 
#include "ex00/ft_ft.c"
#include "ex01/ft_ultimate_ft.c"
#include "ex02/ft_swap.c"
#include "ex03/ft_div_mod.c"
#include "ex04/ft_ultimate_div_mod.c"
#include "ex05/ft_putstr.c"
#include "ex06/ft_strlen.c"
#include "ex07/ft_strrev.c"
#include "ex08/ft_atoi.c"
#include "ex09/ft_sort_integer_table.c"
 
int     main(void)
{
    char str[20] = "\n\n- Exo #00:\n";
    write(1, str, sizeof(str));
    int a;
    ft_ft(&a);
    ft_putnbr(a);
 
    str[10] = '1';
    write(1, str, sizeof(str));
    int p = 101;
    int *p1 = &p;
    int **p2 = &p1;
    int ***p3 = &p2;
    int ****p4 = &p3;
    int *****p5 = &p4;
    int ******p6 = &p5;
    int *******p7 = &p6;
    int ********p8 = &p7;
    int *********p9 = &p8;
    ft_ultimate_ft(p9);
    ft_putnbr(*********p9);
 
    str[10] = '2';
    write(1, str, sizeof(str));
    a = 6;
    int b = -10;
    ft_putnbr(a);
    ft_putchar(',');
    ft_putnbr(b);
    ft_putchar('\n');
    ft_swap(&a, &b);
    ft_putnbr(a);
    ft_putchar(',');
    ft_putnbr(b);
    ft_putchar('\n');
 
    str[10] = '3';
    write(1, str, sizeof(str));
    int div;
    int mod;
    a = 500;
    b = 25;
    ft_div_mod(a, b, &div, &mod);
    ft_putnbr(a);
    ft_putchar('/');
    ft_putnbr(b);
    ft_putchar('=');
    ft_putnbr(div);
    ft_putchar('r');
    ft_putnbr(mod);
    ft_putchar('\n');
 
    str[10] = '4';
    write(1, str, sizeof(str));
    ft_ultimate_div_mod(&a, &b);
    ft_putnbr(a);
    ft_putchar(',');
    ft_putnbr(b);
    ft_putchar('\n');
 
    str[10] = '5';
    write(1, str, sizeof(str));
    char strtest[40] = "Omae wa mou shindeiru.";
    ft_putstr(strtest);
 
    str[10] = '6';
    write(1, str, sizeof(str));
    char strtest2[10] = "Nani ??";
    ft_putnbr(ft_strlen(strtest2));
    ft_putchar('=');
    ft_putnbr(7);
    ft_putchar('\n');
 
    str[10] = '7';
    write(1, str, sizeof(str));
    char revstr_test[20];
    strcpy(revstr_test, ft_strrev(strtest2));
    ft_putstr(revstr_test);
	
    str[10] = '8';
    write(1, str, sizeof(str));
    char intstr[11] = "1234567890";
    ft_putnbr(ft_atoi(intstr));

    str[10] = '9';
    write(1, str, sizeof(str));
    int test[20] = {234,45,67,3,5,64,2,3,5,65,67,300};
    ft_sort_integer_table(test, 12);
    int i;
    for(i = 0; i < 12; i++)
    {  
        ft_putnbr(test[i]);
        ft_putchar(',');
        ft_putchar(' ');
    }
    return (0);
}
