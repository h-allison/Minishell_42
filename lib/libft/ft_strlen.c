/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:43:57 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:30:33 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The  strlen()  function  calculates the length of the string pointed to by s,
excluding the terminating null byte ('\0').
*/
/*
#include <stdio.h>
#include <ctype.h>
#include <string.h>
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*
int	main(void)
{
	char	*s;

	s = "123";

	printf("%zu\n", strlen(s));
	printf("%i\n", ft_strlen(s));
	return (0);
}
*/
