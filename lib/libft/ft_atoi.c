/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:52:50 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:12:03 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
       The  atoi() function converts the initial portion of the string pointed
       to by nptr to int.

       The converted value or 0 on error.

*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "libft.h"
#define TEST_FT atoi

int	ft_is_whitespace(const char nptr)
{
	if (nptr == ' ' || nptr == '\t' || nptr == '\n'
		|| nptr == '\r' || nptr == '\v' || nptr == '\f')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char	*nptr)
{
	int	i;
	int	sign;
	int	base;

	i = 0;
	sign = 1;
	base = 0;
	while (ft_is_whitespace(nptr[i]))
		i++;
	if (nptr[i] == '+' && (nptr[i + 1] < '0' || nptr[i + 1] > '9'))
		return (0);
	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		base = (base * 10) + nptr[i] - '0';
		i++;
	}
	return (sign * base);
}
/*
int	main(void)
{
	char	charnumber[] = "2147483647";
	printf("INT_MIN = %i\n", INT_MAX);
	printf("atoi: %i\n", (atoi(charnumber)));
	printf("ft_atoi: %i\n", (ft_atoi(charnumber)));
	return(0);
}
*/
