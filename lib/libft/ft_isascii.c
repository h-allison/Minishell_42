/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:56:05 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:25:43 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	isascii() checks whether c is a 7-bit unsigned char value that fits 
	into the ASCII character set.
*/

/*
#include <stdio.h>
#include <ctype.h>
*/
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*
int	main(void)
{
	char	c;

	c = 'Q';
	printf("%i\n", isascii(c));
	printf("%i\n", ft_isascii(c));
	return(0);
}
*/
