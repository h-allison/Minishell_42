/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:53:51 by hallison          #+#    #+#             */
/*   Updated: 2024/05/23 12:55:47 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
	Allocates (with malloc(3)) and returns a substring from the string
	's'. The substring begins at index 'start' and is of max size 'len'

	s = the string from which to create the substring.
	start = the start index of the substring in the string 's.'
	len = the maximum length of the substring.
	Return value = the substring, or NULL of the allocation fails.
	
	Returning an empty string if (start > ft_strlen(s) is based on
	testing with francinette.

	ft_substr() segfaults if I do not protect against calloc(SIZE_T)
	in my calloc function. I've tried various shields against SIZE_T
	within substr and none of them suffice.
*/

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#define TEST_FT ft_substr

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;

	if (len <= 0)
		return (ft_calloc(1, 1));
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (start + len > ft_strlen(s))
		len = (ft_strlen(s) - start);
	substring = malloc(len + 1);
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
/*
int	main(void)
{
	char const	s[]  = "hola";
	unsigned int	start = -1;
	size_t	size = -1;
	printf("\nString: %s\n", s);
	printf("Start = %i\n", start);
	printf("Substring: %s\n", TEST_FT(s, start, size));
//	printf("Strlen: %zu\n", ft_strlen(TEST_FT(s, start, size)));
	return (0);
}
*/
