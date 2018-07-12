#include <unistd.h>

#include "ex00/ft_print_alphabet.c"
#include "ex01/ft_print_reverse_alphabet.c"
#include "ex02/ft_print_numbers.c"
#include "ex03/ft_is_negative.c"
#include "ex04/ft_print_comb.c"
#include "ex05/ft_print_comb2.c"
#include "ex06/ft_putnbr.c"
#include "ex07/ft_print_combn.c"

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}


int main()
{
	char exo[] = "\n\n- Exo #00:\n";
	write(1, exo, sizeof(exo));
	ft_print_alphabet();

	exo[10] = '1';
	write(1, exo, sizeof(exo));
	ft_print_reverse_alphabet();

	exo[10] = '2';
	write(1, exo, sizeof(exo));
	ft_print_numbers();

	exo[10] = '3';
	write(1, exo, sizeof(exo));
	ft_is_negative(1);
	ft_putchar('\n');
	ft_is_negative(-1);
	ft_putchar('\n');
	ft_is_negative(0);

	exo[10] = '4';
	write(1, exo, sizeof(exo));
	ft_print_comb();

	exo[10] = '5';
	write(1, exo, sizeof(exo));
	ft_print_comb2();

	exo[10] = '6';
	write(1, exo, sizeof(exo));
	ft_putnbr(123456);
	ft_putchar('\n');
	ft_putnbr(-789);
	ft_putchar('\n');
	ft_putnbr(0);
	ft_putchar('\n');
	ft_putnbr(-2147483648);

	exo[10] = '7';
	write(1, exo, sizeof(exo));
	ft_print_combn(1);
	ft_putchar('\n');
	ft_print_combn(2);
	ft_putchar('\n');
	ft_print_combn(3);
	ft_putchar('\n');
	ft_print_combn(5);
	ft_putchar('\n');
	ft_print_combn(9);
	ft_putchar('\n');
	return (0);
}
