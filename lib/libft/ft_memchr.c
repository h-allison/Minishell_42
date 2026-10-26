/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:52:09 by hallison          #+#    #+#             */
/*   Updated: 2024/05/09 14:35:43 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   The  memchr()  function  scans  the  initial n bytes of the memory area
   pointed to by s for the first instance of c.  Both c and the  bytes  of
   the memory area pointed to by s are interpreted as unsigned char.

   Returns a pointer to the matching byte or NULL if the character does not
   occur in the given memory area.
*/

#include <string.h>
#include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*charptr;
	unsigned char	charc;
	size_t			i;

	charptr = (unsigned char *)s;
	i = 0;
	charc = c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (charptr[i] == charc)
		{
			return ((void *)&charptr[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
//	char	c = '2';
	char s[] = {0, 1, 2 ,3 ,4 ,5};
//	char string[] = "ABC123ABC123";
//	printf("%s\n", string);
	printf("%s\n", (char *)memchr(s, 0, 0));
}
*/
