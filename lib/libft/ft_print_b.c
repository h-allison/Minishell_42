/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flexitoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:50:30 by hallison          #+#    #+#             */
/*   Updated: 2024/08/12 12:30:50 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  This is an adaptation of my general-purpose atoi function that will print
  an int in binary and a minimum of 8 digits. (0000 0000)
*/
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "libft.h"

static int	get_len(size_t nbr, int base)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / base;
		count++;
	}
	return (count);
}

int	ft_print_b(size_t nbr, int base, const char *radix)
{
	int		count;
	int		i;
	int		more_zeros;
	char	str[65];

	count = get_len(nbr, base);
	more_zeros = 8;
	write(1, "0b", 2);
	while (more_zeros > count)
	{
		write(1, "0", 1);
		more_zeros--;
	}
	i = count - 1;
	if (nbr == 0)
		str[0] = radix[0];
	while (nbr != 0)
	{
		str[i] = radix[nbr % base];
		nbr = nbr / base;
		i--;
	}
	str[count] = '\0';
	return (ft_print_s(str));
}

/*
int	main(void)
{
//	ft_flexitoa(42, 16, "0123456789abcdef");
//	printf("\n%x\n", 42);
//	ft_flexitoa(42, 10, "0123456789");
//	printf("\n%d\n", 42);
	printf(" %u ", 0);
	printf("\n");
	ft_printf(" %u ", 0);
}
*/
