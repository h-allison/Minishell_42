/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:53 by hallison          #+#    #+#             */
/*   Updated: 2024/05/09 13:43:46 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   The strcmp() function compares the two strings s1 and s2.*
   strcmp() returns an integer indicating the result of the comparison,
   as follows:

       • 0, if the s1 and s2 are equal;
       • a negative value if s1 is less than s2;
       • a positive value if s1 is greater than s2.
   
   The  strncmp()  function is similar, except it compares only the first
   (at most) n bytes of s1 and s2.
*/

/*
Why is my return value 1/3 of the actual functions' return value?
*/

#include <string.h>
#include <stdio.h>
#define TEST_FT

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*string1 = "";
	char	*string2 = "A";
//	int	array1[6] = {1, 2, 3, 4, 5, 6};
	
	printf("%i\n", (strncmp(string1, string2, 6)));
	printf("%i\n", (ft_strncmp(string1, string2, 6)));
	return(0);
}
*/
