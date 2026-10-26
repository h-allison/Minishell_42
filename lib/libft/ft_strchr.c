/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:50:41 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 15:16:09 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  The  strchr() function returns a pointer to the first occurrence of the
  character c in the string s.
*/

#include <string.h>
#include <stdio.h>

#include "libft.h"
#define TEST_FT strchr

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*tempstring;
	char	x;

	x = (char)c;
	tempstring = (char *)s;
	i = 0;
	while (tempstring[i] != x && s[i] != '\0')
		i++;
	if (tempstring[i] == x)
		return (&tempstring[i]);
	else
		return (NULL);
}
/*
int	main(void)
{
//	char	string[] = "ABCDEF";
	char	string[] = "teste";	
	printf("%s\n", TEST_FT(string, 'e' + 256));
	printf("%c\n", 'e' + 256);
	char *result = TEST_FT(string, 'x');
	if (result != NULL)
	{
		printf("%s\n", result);
	}
	return(0);
}
*/
