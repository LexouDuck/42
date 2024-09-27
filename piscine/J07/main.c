#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "ex00/ft_strdup.c"
#include "ex01/ft_range.c"
#include "ex02/ft_ultimate_range.c"
#include "ex03/ft_concat_params.c"
#include "ex04/ft_split_whitespaces.c"
#include "ex05/ft_print_words_tables.c"
#include "ex06/ft_convert_base.c"
#include "ex07/ft_split.c"

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

int main(void)
{
	int length;
	char *ptr = NULL;
	char str[20] = "\n\nExo 00 :\n";
	char *test = (char*)malloc(23);	
	strcpy(test, "Omae wa mou shindeiru.");
	
	str[7] = '0'; printf("%s", str);
	printf("Test:%s | Expected:%s\n", ft_strdup(test), "Omae wa mou shindeiru.");
	printf("Test:%p | Expected:%p\n", ft_strdup(ptr), ptr);



	str[7] = '1'; printf("%s", str);
	int *array;
	length = 10;
	array = malloc(length * 4);
	array = ft_range(0, 10);
	printf("Test:     [ ");
	for (int i = 0; i < length - 1; i++)
		printf("%d, ", array[i]);
	printf("%d ]\n", array[length - 1]);
	printf("Expected: %s\n\n", "[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]");
	free(array);
	length = 12;
	array = malloc(length * 4);
	array = ft_range(-4, 8);
	printf("Test:     [ ");
	for (int i = 0; i < length - 1; i++)
		printf("%d, ", array[i]);
	printf("%d ]\n", array[length - 1]);
	printf("Expected: %s\n\n", "[ -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 ]");
	free(array);
	printf("Test: %p | Expected: %p\n", ft_range(6, -5), ptr);



	str[7] = '2'; printf("%s", str);
	int **range;
   	range = malloc(8);
	length = ft_ultimate_range(range, 0, 10);
	printf("Test:     [ ");
	for (int i = 0; i < length - 1; i++)
		printf("%d, ", *(*range + i));
	printf("%d ]\n", *(*range + length - 1));
	printf("Expected: %s\n\n", "[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]");
	free(*range);
	free(range);
	range = malloc(8);
	length = ft_ultimate_range(range, -6, 2);
	printf("Test:     [ ");
	for (int i = 0; i < length - 1; i++)
		printf("%d, ", *(*range + i));
	printf("%d ]\n", *(*range + length - 1));
	printf("Expected: %s\n\n", "[ -6, -5, -4, -3, -2, -1, 0, 1 ]");
	free(*range);
	free(range);
	range = malloc(8);
	printf("Test: %d | Expected: %d\n", ft_ultimate_range(range, 6, -5), 0);
	printf("Test: %p | Expected: %p\n\n", *range, ptr);
	free(range);
	range = NULL;
	printf("Test: %d | Expected: %d\n", ft_ultimate_range(range, 0, 5), 0);
	printf("Test: %p | Expected: %p\n", range, ptr);



	str[7] = '3'; printf("%s", str);
	char **strs;
	length = 4;
	strs = malloc(length * 8);
	*strs = { "Omae", "wa", " mou ", " shindeiru." };
	printf("Test:\n%s\nExpected:\n%s\n", ft_concat_params(length, strs), "Omae\nwa\n mou \n shindeiru. ");
	for (int i = 0; i < length; i++)
		free(strs[i]);



	str[7] = '4'; printf("%s", str);
	*test = (char*)malloc(25);	
	strcpy(test, "Omae   wa\nmou\tshindeiru.");
	strs = ft_split_whitespaces(test);
	printf("Test:     [ ");
	for (int i = 0; i < length - 1; i++)
		printf("%s, ", strs[i]);
	printf("%s ]\n", strs[length - 1]);
	printf("Expected: %s\n\n", "[ Omae, wa, mou, shindeiru. ]");



	str[7] = '5'; printf("%s", str);
	printf("Test:\n")
	ft_print_words_tables(strs);
	printf("\nExpected: (same as previous exercice)\n", ft_print_words_tables(ptr), ptr);



	str[7] = '6'; printf("%s", str);
	printf("Test:%s | Expected:%s\n", ft_convert_base("abc", "_abcdefghi", "0123456789"), "123");
	printf("Test:%s | Expected:%s\n", ft_convert_base("1234", "0123456789", "0swag56789"), "123");
	printf("Test:%s | Expected:%s\n", ft_convert_base("ac", "_abcdefghi", "_."), ".._.");


	str[7] = '7'; printf("%s", str);
	printf("Test:%p | Expected:%p\n", ft_split(ptr), ptr);
}
