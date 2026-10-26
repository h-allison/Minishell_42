/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:28 by hallison          #+#    #+#             */
/*   Updated: 2024/09/09 15:42:06 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/
#include <stdio.h>
#include "libft.h"

int	int_len(long int num)
{
	int	int_len;

	int_len = 0;
	if (num == 0)
	{
		return (1);
	}
	if (num < 0)
	{
		int_len++;
		num = num * -1;
	}
	while (num != 0)
	{
		num = num / 10;
		int_len++;
	}
	return (int_len);
}

char	*ft_itoa(int n)
{
	int			string_len;
	char		*itoa_str;
	int			i;
	long int	num;

	num = n;
	string_len = int_len(num);
	itoa_str = ft_calloc((string_len + 1), sizeof(char));
	if (!itoa_str)
		return (NULL);
	if (num == 0)
		itoa_str[0] = '0';
	if (num < 0)
	{
		itoa_str[0] = '-';
		num = num * -1;
	}
	i = string_len - 1;
	while (num != 0)
	{
		itoa_str[i] = ((num % 10) + 48);
		num = num / 10;
		i--;
	}
	return (itoa_str);
}
/*
int	main(void)
{
	printf("\n");
	int n = -623;
	printf("int n = %d\n", n);
	char *x = ft_itoa(n);"

	printf("ft_itoa(%d) = %s\n\n", n, x);
	return (0);
}
*/
