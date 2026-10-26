/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:36:59 by hallison          #+#    #+#             */
/*   Updated: 2024/08/12 12:26:53 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 %i and %d are interchangeable when used with printf.
 Both are used to print an integer in decimal (base 10) format.

 If I was writing a scanf function, there would be a difference.
 In scanf(), %d handles decimal (base 10) integers,
 while %i can handle a variety of bases (decimal, hexidecimal, or octal).
*/
#include <unistd.h>
#include "libft.h"

int	get_int_len(long int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		count++;
		nbr = nbr * -1;
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

int	ft_print_d(int nbr)
{
	int		count;
	int		i;
	char	decimal_str[12];

	count = get_int_len(nbr);
	if (nbr == 0)
		decimal_str[0] = '0';
	if (nbr == -2147483648)
		return (ft_print_s ("-2147483648"));
	if (nbr < 0)
	{
		decimal_str[0] = '-';
		nbr = nbr * -1;
	}
	i = count - 1;
	while (nbr != 0)
	{
		decimal_str[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	decimal_str[count] = '\0';
	return (ft_print_s(decimal_str));
}
