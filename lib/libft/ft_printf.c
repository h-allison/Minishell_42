/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:12:48 by hallison          #+#    #+#             */
/*   Updated: 2024/06/17 14:26:16 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 • %c Prints a single character.
 • %s Prints a string (as defined by the common C convention).
 • %p The void * pointer argument has to be printed in hexadecimal format.
 • %d Prints a decimal (base 10) number.
 • %i Prints an integer in base 10.
 • %u Prints an unsigned decimal (base 10) number.
 • %x Prints a number in hexadecimal (base 16) lowercase format.
 • %X Prints a number in hexadecimal (base 16) uppercase format.
 • %% Prints a percent sign.

 My tests show that original printf()
 returns a count of how many chars it wrote.
 There is no null byte included in the return count.

 va_list is used by functions with a varying number of arguments of  varying
 types.   The  function  must  declare  an object of type va_list which is
 used by the macros va_start(3), va_arg(3),  va_copy(3),
 and va_end(3) to traverse the list of arguments.
*/
#define BASE2_RADIX "01"
#define BASE10_RADIX "0123456789"
#define BASE16_RADIX "0123456789abcdef"
#define BASE16_RADIX_U "0123456789ABCDEF"

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "ft_printf.h"

static void	ft_fmt(const char *format, va_list args, int *count, int i)
{
	if (format[i] == 'c')
		*count = *count + ft_print_c(va_arg(args, int));
	else if (format[i] == 's')
		*count = *count + ft_print_s (va_arg (args, char *));
	else if (format[i] == 'd' || format[i] == 'i')
		*count += ft_print_d (va_arg(args, int));
	else if (format[i] == 'b')
		*count += ft_print_b(va_arg(args, unsigned int), 2, BASE2_RADIX);
	else if (format[i] == 'u')
		*count += ft_flexitoa(va_arg(args, unsigned int), 10, BASE10_RADIX);
	else if (format[i] == 'x')
		*count += ft_flexitoa(va_arg(args, unsigned int), 16, BASE16_RADIX);
	else if (format[i] == 'X')
		*count += ft_flexitoa(va_arg(args, unsigned int), 16, BASE16_RADIX_U);
	else if (format[i] == 'p')
		*count = *count + ft_print_p(va_arg(args, void *));
	else if (format[i] == '%')
		*count = *count + ft_print_c ('%');
	else
		write(1, " (ERROR -- Unknown format specifier) ", 37);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			write (1, &format[i], 1);
			count++;
		}
		else
		{
			i++;
			ft_fmt(format, args, &count, i);
		}
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
//	char	letter = 'X';
//	char	string[] = "ABC";
//	void	*ptr = &string;
//	int	decimal = -1000;
//	int	integer = 100;
//	unsigned int	unsigneddec = 42;
//	int	i = ft_printf("%u", integer);
//	int	j = ft_printf("%s", string);
//	printf("\nreturn value = %d", i);
//	printf("\nreturn value = %d", j);
//	printf("ptr = %p", string);
//	int	i = ft_printf(" %x ", -1);
//	printf("\n%x", i);
//

//      // CATEGORY u, Test 24:
	int i = printf(" %u ", 2147483647);
	printf("\n");
	int j = ft_printf(" %u ", 2147483647);
	printf("\n");
	printf("%d vs. %d", i, j);

//	// CATEGORY S, Test 6:
//	int i = printf(" %s %s %s %s %s ", " - ", "", "4", "", "2");
//	printf("\n");
//	int j = ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2");
//	printf("\n");
//	printf("%d vs. %d", i, j);

//      // CATEGORY S, Test 6:
//      int i = printf(" %s %s %s %s %s ", " - ", "", "4", "", "2");
//      printf("\n");
//      int j = ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2");
//      printf("\n");
//      printf("%d vs. %d", i, j);

//	// CATEGORY S, Test 10:
//	int i = printf(" NULL %s NULL ", (char *)NULL);
//	printf("\n");
//	int j = ft_printf(" NULL %s NULL ", (char *)NULL);
//	printf("\n");
//	printf("%d vs. %d", i, j);
//	return(0);

//	// CATEGORY P, Test 6:
//	int i = printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
//	printf("\n");
//	int j = ft_printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
//	printf("\n");
//	printf("%d vs. %d", i, j);
//	return(0);


}
*/
