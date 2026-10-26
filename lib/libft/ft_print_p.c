/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:41:23 by hallison          #+#    #+#             */
/*   Updated: 2024/08/12 12:28:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The void * pointer argument has to be printed in hexadecimal format.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "libft.h"

int	ft_print_p(void *arg)
{
	uintptr_t	address;

	if (arg == 0)
		return (ft_print_s("(nil)"));
	address = (uintptr_t)arg;
	return (ft_print_s("0x") + ft_flexitoa(address, 16, "0123456789abcdef"));
}
/*
int	main(void)
{
//	char	*ptr = "random";
//	ft_print_p(ptr);
	printf(" %p %p \n", (void *)LONG_MIN, (void *)LONG_MAX);
	ft_printf(" %p %p ", LONG_MIN, LONG_MAX);
//	TEST(6, print(" %p %p ", LONG_MIN, LONG_MAX));
//	TEST(8, print(" %p %p ", ULONG_MAX, -ULONG_MAX));
}
*/
