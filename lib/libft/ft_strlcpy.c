/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:20:58 by hallison          #+#    #+#             */
/*   Updated: 2024/05/08 19:12:39 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   The original strlcpy() function requires <bsd/string.h> AND -lbsd when
   compiling.

   Strlcpy() copies strings and is designed to be safer, more consistent, &
   less error-prone than strncpy. Unlike strncpy, strlcpy takes the full size
   of the buffer (not just the length) and guarantees to NUL-terminate the
   result (as long as size is larger than 0). A byte for the nul should be
   included in size.

   Only operates on true “C” strings.  For strlcpy this means that src must be 
   NUL-terminated.

   Strlcpy() returns the total length of the string it tried to create,
   which is the same as the length of src.
*/

#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
// #include <bsd/string.h>
#define TEST_FT strlcpy

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;	

	src_len = (ft_strlen((char *)src));
	if (size == 0)
		return (src_len);
	if (size > src_len + 1)
		ft_memcpy(dst, src, src_len + 1);
	else
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (src_len);
}
/*
// My TEST MAIN
int	main(void)
{
	char	src[5] = "abc\0";
	char	dst[7] = "123456";
	int	blah[2][2] = {{1, 2}, {3, 4}};
	size_t	buffer = 9;
	printf("src: %s\n", src);
	printf("dst: %s\n", dst);	
	printf("<<Function Test>>\nreturn value: %zu\n", TEST_FT(dst, src, buffer));
	printf("dest: %s\n", dst);
	printf("size of dst: %lu\n", sizeof(dst));
	printf("size of blah: %lu\n", sizeof(blah));
	unsigned int	i;
	i = 0;
	while (i < sizeof(dst))
	{
		write (1, &dst[i], 1);
		i++;
	}

	printf("\n\n");

	return (0);
}
*/
/*
// Adapted from Francinette TEST MAIN
int	main(void)
{
 	char *str = "hello !";
 	char buff1[0xF00];
 	char buff2[0xF00];
 	size_t r1;
 	size_t r2;
 
 	memset(buff1, 'A', 20);
 	memset(buff2, 'A', 20);
 	r1 = strlcpy(buff1, str, 2);
 	r2 = ft_strlcpy(buff2, str, 2);
 	printf("strlcpy return value: %zu\n", r1);
	printf("ft_strlcpy return value: %zu\n", r2);
	return (0);
}
*/
