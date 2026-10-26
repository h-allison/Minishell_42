/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:45:22 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:26:28 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
isxdigit() checks for checks for a digit (0 through 9).
*/
/*
#include <ctype.h>
#include <stdio.h>
*/
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

/*
int	main(void)
{
	int	c;

	c = '0';
	printf("%i\n", isdigit(c));
	printf("%i\n", ft_isdigit(c));
	return (0);
}
*/
