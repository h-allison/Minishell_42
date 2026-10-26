/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:52:38 by hallison          #+#    #+#             */
/*   Updated: 2024/05/23 00:05:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
     Origiinal function requires -lbsd flag when compiling.

     The strnstr() function locates the first occurrence of the
     null-terminated string little in the string big, where not more than
     len characters are searched.  Characters that appear after a ‘\0’
     character are not searched.

     If little is an empty string, big is returned; if little occurs
     nowhere in big, NULL is returned; otherwise a pointer to the first
     character of the first occurrence of little is returned.
*/

//#include <bsd/string.h>
#include <string.h>
#include <stdio.h>

#include "libft.h"

char	*ft_needle_search(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	j = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			temp = i;
			while (big[i] == little[j] && little && i < len)
			{
				i++;
				j++;
			}
			if (little[j] == '\0')
				return ((char *)&big[temp]);
			j = 0;
			i = temp;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (little[0] == '\0' || little == NULL)
		return ((char *)big);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	return (ft_needle_search(big, little, len));
}
/*
int	main(void)
{
	char	big[] = "aaabcabcd";
	char	little[] = "aabc";
	printf("strnstr = %s\n", strnstr(big, little, -1));
	printf("ft_strnstr = %s\n", ft_strnstr(big, little, -1));
	return(0);
}
*/
