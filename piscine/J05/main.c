#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#include "ex00/ft_putstr.c"
#include "ex01/ft_putnbr.c"
#include "ex02/ft_atoi.c"
#include "ex03/ft_strcpy.c"
#include "ex04/ft_strncpy.c"
#include "ex05/ft_strstr.c"
#include "ex06/ft_strcmp.c"
#include "ex07/ft_strncmp.c"
#include "ex08/ft_strupcase.c"
#include "ex09/ft_strlowcase.c"
#include "ex10/ft_strcapitalize.c"
#include "ex11/ft_str_is_alpha.c"
#include "ex12/ft_str_is_numeric.c"
#include "ex13/ft_str_is_lowercase.c"
#include "ex14/ft_str_is_uppercase.c"
#include "ex15/ft_str_is_printable.c"
#include "ex16/ft_strcat.c"
#include "ex17/ft_strncat.c"
#include "ex18/ft_strlcat.c"
#include "ex19/ft_strlcpy.c"
#include "ex20/ft_putnbr_base.c"
//#include "ex21/ft_atoi_base.c"
//#include "ex22/ft_putstr_non_printable.c"
//#include "ex23/ft_print_memory.c"

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

int main(void)
{

	char str[20] = "\n\nExo 00 :\n";
	
	str[7] = '0'; write(1, str, sizeof(str));
	char *test;
   	test = (char*)malloc(23);	
	strcpy(test, "Omae wa mou shindeiru.");
	ft_putstr(test);

	str[7] = '1'; write(1, str, sizeof(str));
	ft_putnbr(42);
	ft_putchar('\n');
	ft_putnbr(-2147483648);
	ft_putchar('\n');
	ft_putnbr(0);
	
	str[7] = '2'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_atoi("0"), "0");
	printf("Test:%d | Expected:%s\n", ft_atoi("65535"), "65535");
	printf("Test:%d | Expected:%s\n", ft_atoi("-2147483648"), "-2147483648");
	printf("Test:%d | Expected:%s\n", ft_atoi("--456"), "0 (given str was --456)");
	printf("Test:%d | Expected:%s\n", ft_atoi("swag42"), "0 (given str was swag42)");

	str[7] = '3'; printf("%s", str);
	printf("Test:%s | Expected:%s\n", ft_strcpy(test, "swag"), "swag");

	str[7] = '4'; printf("%s", str);
	strcpy(test, "Omae wa mou shindeiru.");
	printf("Test:%s | Expected:%s\n", ft_strncpy(test, "Swag", 4), "Swag wa mou shindeiru.");

	str[7] = '5'; printf("%s", str);
	strcpy(test, "Omae wa mou shindeiru.");
	char *p = 0;
	printf("Test:%p | Expected:%p\n", ft_strstr(test, "wa "), test + 5);
	printf("Test:%p | Expected:%p\n", ft_strstr(test, "swag"), p);

	str[7] = '6'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_strcmp("swag1", "swag2"), "-1");
	printf("Test:%d | Expected:%s\n", ft_strcmp("swag", "swag"), "0");
	printf("Test:%d | Expected:%s\n", ft_strcmp("swag2", "swag1"), "1");

	str[7] = '7'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_strncmp("swag1", "swag2", 5), "-1");
	printf("Test:%d | Expected:%s\n", ft_strncmp("swag1", "swag2", 2), "0");

	str[7] = '8'; printf("%s", str);
	printf("Test:%s | Expected:%s\n", ft_strupcase(test), "OMAE WA MOU SHINDEIRU.");

	str[7] = '9'; printf("%s", str);
	strcpy(test, "omAe wA mOu ShINDeIRu.");
	printf("Test:%s | Expected:%s\n", ft_strlowcase(test), "omae wa mou shindeiru.");

	str[6] = '1'; str[7] = '0'; printf("%s", str);
	test = strcpy(test, "omAe wA MOu ShInDeIRu.");
	printf("Test:%s | Expected:%s\n", ft_strcapitalize(test), "Omae Wa Mou Shindeiru.");
	test = strcpy(test, "OMAE wa moU SHindeiru.");
	printf("Test:%s | Expected:%s\n", ft_strcapitalize(test), "Omae Wa Mou Shindeiru.");
	test = strcpy(test, "AHxzavvimbhdmhrhjriyluybuntoncbfkoydrfwe");
	printf("Test:%s | Expected:%s\n", ft_strcapitalize(test), "Ahxzavvimbhdmhrhjriyluybuntoncbfkoydrfwe");


	str[7] = '1'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_str_is_alpha("Nani"), "1");
	printf("Test:%d | Expected:%s\n", ft_str_is_alpha("Nani ??"), "0");
	printf("Test:%d | Expected:%s\n", ft_str_is_alpha(""), "1 (empty str)");

	str[7] = '2'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_str_is_numeric("456789123000"), "1");
	printf("Test:%d | Expected:%s\n", ft_str_is_numeric("-45612"), "0");
	printf("Test:%d | Expected:%s\n", ft_str_is_numeric(""), "1 (empty str)");

	str[7] = '3'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_str_is_lowercase("nani"), "1");
	printf("Test:%d | Expected:%s\n", ft_str_is_lowercase("nani ??"), "0");
	printf("Test:%d | Expected:%s\n", ft_str_is_lowercase(""), "1 (empty str)");

	str[7] = '4'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_str_is_uppercase("NANI"), "1");
	printf("Test:%d | Expected:%s\n", ft_str_is_uppercase("NANI ??"), "0");
	printf("Test:%d | Expected:%s\n", ft_str_is_uppercase(""), "1 (empty str)");

	str[7] = '5'; printf("%s", str);
	printf("Test:%d | Expected:%s\n", ft_str_is_printable("Nani ??"), "1");
	printf("Test:%d | Expected:%s\n", ft_str_is_printable("\14Nani\29??"), "0");
	printf("Test:%d | Expected:%s\n", ft_str_is_printable(""), "1 (empty str)");

	str[7] = '6'; printf("%s", str);
	strcpy(test, "Sponge\0");
	printf("Test:%s | Expected:%s\n", ft_strcat(test, "Bob"), "SpongeBob");
	
	str[7] = '7'; printf("%s", str);
	strcpy(test, "Sponge\0");
	printf("Test:%s | Expected:%s\n", ft_strncat(test, "Bobensen", 3), "SpongeBob");
	
	str[7] = '8'; printf("%s", str);
	char *test2;
	test2 = (char*)malloc(15);
    strcpy(test2, "Omae wa mou");
	printf("Test:%d | Expected:%d\n", ft_strlcat(test2, " shindeiru", 15), 21);
	printf("Test:%s | Expected:%s\n", test2, "Omae wa mou sh"); //faut pas oublier \0

	str[7] = '9'; printf("%s", str);
	test2[0] = '\0';
	printf("Test:%d | Expected:%d\n", ft_strlcpy(test2, "Omae wa mou shindeiru", 15), 21);
	printf("Test:%s | Expected:%s\n", test2, "Omae wa mou sh"); //faut pas oublier \0

	str[6] = '2'; str[7] = '0'; write(1, str, 11);
	write(1, "Test: ", 6);
	ft_putnbr_base(1000, "0123456789abcdef");
	ft_putnbr_base(-2147483648, "0123456789abcdef");
	ft_putnbr_base(0, "*&%^0");
	write(1, ", Expected: 3e8-80000000*", 25);
/*
	str[7] = '1'; printf("%s", str);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("mmmm", "m"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("00101010", "01"), 42);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("momomom", "mom"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("4+", "01+3456789"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("0124023e03", "0123456789"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("-3e8", "0123456789abcdef"), -1000);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("*xurin", "grincheux*"), 987123);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("   -3e8", "0123456789abcdef"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("+-2A", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("++2A", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("--2A", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("-+2A", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("+-", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("++", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("-+", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("--", "0123456789ABCDEF"), 0);

	printf("Test:%d | Expected:%d\n", ft_atoi_base("2-A", "0123456789ABCDEF"), 2);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("+2-A", "0123456789ABCDEF"), 2);
	printf("Test:%d | Expected:%d\n", ft_atoi_base("2a", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base( "", "0123456789ABCDEF"), 0);
	printf("Test:%d | Expected:%d\n", ft_atoi_base( "-0000F", "0123456789ABCDEF"), -15);

	str[7] = '2'; write(1, str, 11);
	write(1, "Test: ", 6);
	ft_putstr_non_printable("Coucou\ntu\tvas\vbien ?");
	write(1, ", Expected: Coucou\\0atu\\09vas\\0bbien ?", 38);

	str[7] = '3'; printf("%s", str);
	char *ptr = "These violent delights have violent ends.";
	ft_print_memory(ptr, 41);*/
}
