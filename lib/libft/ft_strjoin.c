/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:02 by hallison          #+#    #+#             */
/*   Updated: 2024/05/20 20:20:40 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Allocates (with malloc(3)) and returns a new string,
	which is the result of the concatenation of 's2' and 's2'.
	
	s1 = the prefix string.
	s2 = the suffic string.
	
	Return value = the new string, or NULL if allocation fails.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	new_len;

	if (!s1 && !s2)
		return (ft_strdup(NULL));
	new_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	new_string = malloc(new_len);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, new_len);
	ft_strlcpy(new_string + ft_strlen(s1), s2, (new_len - ft_strlen(s1)));
	return (new_string);
}
/*
int	main(void)
{

	char 	s1[] = "where is my ";
	char	s2[] = "malloc ???";
	char	s3[] = "where is my malloc ???";
	printf("%s\n", ft_strjoin(s1, s2));
	char *res = ft_strjoin(s1, s2);
	if (!strcmp(res, s3))
		printf("The strings are identical.\n");
	else
		printf("Error.\n\n");


	char	s4[] = "lorem ipsum";
	char	s5[] = "dolor sit amet";
	char	s6[] = "lorem ipsumdolor sit amet";
	printf("%s\n", ft_strjoin(s4, s5));
	char *res2 = ft_strjoin(s4, s5);
	if (!strcmp(res2, s6))
                printf("The strings are identical.\n");
        else
                printf("Error.");

	return(0);
}
*/
