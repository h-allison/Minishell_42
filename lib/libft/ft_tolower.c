/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:20 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:41:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + ('a' - 'A');
	return (c);
}
/*
int	main(void)
{
	int x = 'A';
        printf("%c | %d\n", x, x);

        int y = ft_tolower(x);
        printf("%c | %d\n", y, y);
        return (0);
}
*/
