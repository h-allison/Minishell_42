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
  This is a general-purpose atoi function that is meant to handle all bases
  and radixes. It is intended to replace 3 or 4 separate functions
  that I previously wrote to handle %u, %x, %X, %p  in ft_printf.
*/
#include <stdio.h>
#include <limits.h>
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

int	ft_flexitoa(size_t nbr, int base, const char *radix)
{
	int		count;
	int		i;
	char	str[65];

	count = get_len(nbr, base);
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
