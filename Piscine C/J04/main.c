#include <stdio.h>
#include <time.h>

#include "ex00/ft_iterative_factorial.c"
#include "ex01/ft_recursive_factorial.c"
#include "ex02/ft_iterative_power.c"
#include "ex03/ft_recursive_power.c"
#include "ex04/ft_fibonacci.c"
#include "ex05/ft_sqrt.c"
#include "ex06/ft_is_prime.c"
#include "ex07/ft_find_next_prime.c"
//#include "ex08/ft_eight_queens_puzzle.c"
//#include "ex09/ft_eight_queens_puzzle_2.c"


double	clocktime(clock_t start, clock_t end)
{
	return (end - start) / CLOCKS_PER_SEC;
}

int main()
{
	clock_t start, end;

	char str[20] = "\n\nExo 00 :\n";
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_iterative_factorial(10), 3628800);
	printf("Test: %d; Expected: %d\n", ft_iterative_factorial(-100), 0);	
	printf("Test: %d; Expected: %d\n", ft_iterative_factorial(0), 1);
	printf("Test: %d; Expected: %d\n", ft_iterative_factorial(1), 1);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 2 sec (pas 8), cas triviaux", clocktime(start, end));

	str[7] = '1';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_recursive_factorial(10), 3628800);
	printf("Test: %d; Expected: %d\n", ft_recursive_factorial(-100), 0);
	printf("Test: %d; Expected: %d\n", ft_recursive_factorial(0), 1);
	printf("Test: %d; Expected: %d\n", ft_recursive_factorial(1), 1);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 2 sec (pas 8), cas triviaux", clocktime(start, end));

	str[7] = '2';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_iterative_power(10, 8), 100000000);
	printf("Test: %d; Expected: %d\n", ft_iterative_power(12, -100), 0);	
	printf("Test: %d; Expected: %d\n", ft_iterative_power(12, 0), 1);
	printf("Test: %d; Expected: %d\n", ft_iterative_power(12, 1), 12);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 2 sec (pas 8), cas triviaux", clocktime(start, end));

	str[7] = '3';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_recursive_power(10,8), 100000000);
	printf("Test: %d; Expected: %d\n", ft_recursive_power(12, -100), 0);
	printf("Test: %d; Expected: %d\n", ft_recursive_power(12, 0), 1);
	printf("Test: %d; Expected: %d\n", ft_recursive_power(12, 1), 12);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 2 sec (pas 8), cas triviaux", clocktime(start, end));

	str[7] = '4';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_fibonacci(0), 0);
	printf("Test: %d; Expected: %d\n", ft_fibonacci(-100), -1);
	printf("Test: %d; Expected: %d\n", ft_fibonacci(28), 317811);
	printf("Test: %d; Expected: %d\n", ft_fibonacci(38), 39088169);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 4 sec (pas 8), cas triviaux", clocktime(start, end));

	str[7] = '5';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_sqrt(100000000), 10000);
	printf("Test: %d; Expected: %d\n", ft_sqrt(16777216), 4096);
	printf("Test: %d; Expected: %d\n", ft_sqrt(-12), 0);
	printf("Test: %d; Expected: %d\n", ft_sqrt(1), 1);
	printf("Test: %d; Expected: %d\n", ft_sqrt(0), 0);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 2 sec (pas 8), cas triviaux", clocktime(start, end));

	str[7] = '6';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_is_prime(48539*37813), 0);
	printf("Test: %d; Expected: %d\n", ft_is_prime(-15487469), 0);
	printf("Test: %d; Expected: %d\n", ft_is_prime(373587883), 1);
	printf("Test: %d; Expected: %d\n", ft_is_prime(1), 0);
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 3 sec (pas 8), cas triviaux ou simples", clocktime(start, end));

	str[7] = '7';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_find_next_prime(373587158), 373587191);
	printf("Test: %d; Expected: %d\n", ft_find_next_prime(-2000), 2);
	end = clock();
	printf("2 tours de fonction pour %f secondes, expect < 2 sec (pas 4), cas trivial", clocktime(start, end));
/*
	str[7] = '8';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, ft_eight_queens_puzzle(), 92);
	end = clock();
	printf("1 tours de fonction pour %f secondes, expect < 2 sec", clocktime(start, end));

	str[7] = '9';
	start = clock();
	printf("%sTest: %d; Expected: %d\n", str, );
	printf("Test: %d; Expected: %d\n", );
	printf("Test: %d; Expected: %d\n", );
	printf("Test: %d; Expected: %d\n", );
	end = clock();
	printf("4 tours de fonction pour %f secondes, expect < 4 sec (pas 8), cas triviaux", clocktime(start, end));
*/


	return (0);
}
