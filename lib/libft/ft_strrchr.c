/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:43 by hallison          #+#    #+#             */
/*   Updated: 2024/05/09 11:40:24 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
      	The strrchr() function returns a pointer to the last occurrence of
	the character c in the string s.
*/

#include <string.h>
#include <stdio.h>
#define TEST_FT ft_strrchr

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tempstring;
	char	x;

	x = (char)c;
	tempstring = (char *)s;
	i = 0;
	while (tempstring[i] != '\0')
	{
		i++;
	}
	while (tempstring[i] != x && i != 0)
	{
		i--;
	}
	if (tempstring[i] == x)
	{
		return (&tempstring[i]);
	}
	else
	{
		return (NULL);
	}
}
/*
int	main(void)
{
	char string[] = "teste";
	printf("%s\n", TEST_FT(string, 'x'));
	return(0);
}
*/
