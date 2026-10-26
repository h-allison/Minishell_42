/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:50:38 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 15:14:23 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   The original strlcpy() function requires <bsd/string.h> AND -lbsd when
   compiling.

   Strlcpy() concatenate strings and is designed to be safer, more consistent,
   and less error prone replacements for strncat(3). Unlike strncat, strlcat()
   takes the full size of the buffer (not just the length) and guarantees
   to NUL-terminate the result (as long as size is larger than 0 or as long 
   as there is at least one byte free in dst).  A byte for the NUL should be
   included in size.

   Only operates on true “C” strings.
   Both src and dst must be NUL-terminated.

   The strlcat() function appends the NUL-terminated string src to the end
   of dst.  It will append at most size - strlen(dst) - 1 bytes,
   NUL-terminating the result.

   Strlcat() returns the total length of the string it tried to create,
   which is the initla length of dst plus the length of src.

   However, if strlcat() traverses (size) characters without finding a
   NUL, the length of the string is considered to be (size) and the
   dest string will not be NUL-terminated. In practice this should not
   happen (as it means that either size is incorrect or that dst is not
   a proper "C" string), but this check exists for security.

*/

//#include <bsd/string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define TEST_FT strlcat
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	if (src_len < size - dst_len)
	{
		ft_memcpy(dst + dst_len, src, src_len + 1);
	}
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
/*
int     main(void)
// MY TEST MAIN
{
	char    src[4] = "abc";
	char    dst[3] = "12";
	size_t  buffer = 4;
        printf("\nsrc: %s\n", src);
        printf("dst: %s\n", dst);
 	printf("size of buffer: %lu\n", sizeof(buffer));
	TEST_FT(dst, src, buffer);
	printf("<<FUNCTION TEST>>\nreturn value: %zu\n", TEST_FT(dst, src, buffer));
  	printf("dst: %s\n", dst);
    	printf("size of dst: %lu\n", sizeof(dst));
	printf("^ interesting: this doesn't change\n");

	unsigned int    i;
	i = 0;
       	while (i <= strlen(dst))
       	{
		write (1, &dst[i], 1);
		i++;
       	}
        printf("\n");
	if (dst[strlen(dst)] == '\0')
		printf("The last char is a null terminator.");
	return(0);
}
*/
/*
int	main(void)
// adaptation of Francinette tests
{
	char *str = "the cake is a lie !\0I'm hidden lol\r\n";
 	char buff1[0xF00] = "there is no stars in the sky";
 	char buff2[0xF00] = "there is no stars in the sky";
 	size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;

	printf("Dst length = %zu\n", ft_strlen(str));
	printf("Src length = %zu\n", ft_strlen(buff1));
	printf("Total original length = %zu\n", (ft_strlen(str) + ft_strlen(buff1)));
 	printf("%zu\n", ft_strlcat(buff1, str, max));
	printf("%s\n", buff1);
 	ft_strlcat(buff2, str, max);

	return (0);
}
*/
