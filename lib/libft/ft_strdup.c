/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:53:09 by hallison          #+#    #+#             */
/*   Updated: 2024/05/05 19:27:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strdup()  function returns a pointer to a new string which is a
   duplicate of the string s. Memory for the new string is obtained with
   malloc(3),  and  can  be  freed with free(3).

   On success, the strdup() function returns a pointer to the duplicated string.
   It returns NULL if insufficient memory was available, with errno set to
   indicate the cause of the error.
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#define TEST_FT strdup

char	*ft_strdup(const char *s)
{
	char	*newstr;
	size_t	stringlength;
	size_t	i;

	stringlength = ft_strlen((char *)s);
	newstr = (char *) malloc(stringlength + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < stringlength)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
/*
int	main(void)
{
	const char	string[] = "ABCDEFG";
	const char	*newstring = TEST_FT(string);
	printf("\nString: %s\n", string);
	printf("Address: %p\n", (void *)string);
	printf("Size: %zu\n", sizeof(string));
	printf("New String: %s\n", newstring);
	printf("New Address: %p\n", (void *)newstring);
	printf("Size: %zu\n\n", sizeof(newstring));
}
*/
