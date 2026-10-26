/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:01:44 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:28:21 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	isalnum() checks for an alphanumeric character;
	it is equivalent to (isalpha(c) || isdigit(c)).
*/
#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (8);
	else
		return (0);
}

/*
int	main (void)
{
	int	c;
	
	c = '\0';
	printf("%i\n", isalnum(c));
	printf("%i\n", ft_isalnum(c));
	return (0);
}
*/
