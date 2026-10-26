/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:18:04 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:28:52 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

isprint() checks for any printable character including space.

*/
/*
#include <stdio.h>
#include <ctype.h>
*/
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}

/*
int	main(void)
{
	char	c;
	c = '\n';

//	int	c;
//	c = 128;

	printf("%i\n", isprint(c));
	printf("%i\n", ft_isprint(c));
	return (0);
}
*/
