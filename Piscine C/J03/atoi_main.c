#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 
#define TAB_SIZE(x)  (sizeof(x) / sizeof((x)[0]))
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#include "ex08/ft_atoi.c"

void    print_str(char *str)
{
    int i;
 
    i = 0;
    while (str[i] != '\0')
    {
        if (isprint(str[i]))
            printf("%c", str[i]);
        else if ((str[i] >= 7) && (str[i] <= 13))
            printf("[%d]", (int)(str[i]));
        else
            printf("%c", str[i]);
        i++;
    }
}
 
int     main(void)
{
    int     i;
    int     a;
    int     b;
    char    *str[] = {
        "0",
        "1",
        "42",
        "-5435",
        "--9999999",
        "-2147483648",
        "2147483647",
        "   8543",
        "\f3541",
        "\n5643",
        "\r397+",
        "\t8513",
        "\v9876-",
        "65435+--+",
        "def58453",
        "5486helllo",
        "\f-3541",
        "\n-5643",
        "-\r-397+",
        "---84648-+",
        "&%64",
        "125\n12",
        "  -2",
        "  2",
		"!789",
		"#45",
		"$786",
		"&789",
		"*4456",
		".1234",
		"/1234",
		"%1234",
		",7",
		",,789",
		"456,78",
		".456",
        "  +5896df",
        "  + 563",
        "++4653",
        " + 45631dsf-+"
    };
 
    i = 0;
    while (i < (int)TAB_SIZE(str))
    {
        printf("Testing value: {");
        print_str(str[i]);
        printf("} -> ");
        a = ft_atoi(str[i]);
        b = atoi(str[i]);
        if (a != b)
        {
            printf(RED"error on test {");
            print_str(str[i]);
            printf("}: \n> atoi:{%d}\n> ft_atoi:{%d}\n"RESET, atoi(str[i]), ft_atoi(str[i]));
//            return (-1);
        }
        printf("[%d]\n", a);
        i++;
    }
    printf(GREEN"All tests passed :D\n"RESET);
    return (0);
}
