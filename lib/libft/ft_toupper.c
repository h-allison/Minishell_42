/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:11 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:33:37 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
    if c is a lowercase letter, toupper() returns its uppercase equivalent.
	Otherwise, it returns c.
	If c is neither an unsigned char value nor EOF, the behavior
	if undefined.
*/
/*
#include <ctype.h>
#include <stdio.h>
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - ('a' - 'A');
	return (c);
}
/*
int	main(void)
{
	int c = 'a';
	char x = c;
	printf("%c | %d\n", x, c);
	c = ft_toupper(c);
	x = c;
	printf("%c | %d\n", x, c);
	return (0);
}
*/
