/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:03:14 by hallison          #+#    #+#             */
/*   Updated: 2024/05/08 18:03:52 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   The  memmove()  function  copies  n bytes from memory area src to
   memory area dest.  The memory areas may overlap: copying takes place as
   though the bytes in src are first copied into a temporary array that
   does not overlap src or dest, and  the  bytes  are then copied from the
   temporary array to dest.

   RETURN VALUE -- The memmove() function returns a pointer to dest.
*/

#include <string.h>
#include <stdio.h>
#include "libft.h"
#define TEST_FT ft_memmove

void	ft_copyforward(char *char_dest, const char *char_src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*char_dest;
	const char	*char_src;

	char_dest = (char *)dest;
	char_src = (const char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (char_dest <= char_src || char_dest >= char_src + n)
		ft_copyforward(char_dest, char_src, n);
	else
	{
		while (n > 0)
		{
			char_dest[n - 1] = char_src[n - 1];
			n--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	strings[] = "123456";
	printf("\nORIGINAL SRC: %s\n", strings);
	printf("ORIGINAL DEST: %s\n\n", strings + 1);
	printf("<<FUNCTION TEST>>\n\n");
	TEST_FT(strings, strings + 1, 5);
	printf("SRC: %s\n", strings);
	printf("DEST: %s\n\n", strings + 1);
	return(0);
}
*/
/*
int	main(void)
{
	//francinette test main
	char *src = "thanks to @apellicc for this test !\n";
 	char dst1[0xF0];
// 	char dst2[0xF0];
 	int size = strlen(src);
 
 	TEST_FT(dst1, src, size);
	printf("%s\n", dst1);	
	return(0);
}
*/
