/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:45:00 by hallison          #+#    #+#             */
/*   Updated: 2024/05/08 17:39:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   void *memcpy(void *dest, const void *src, size_t n);

   The memcpy() function copies n bytes from memory area src to
   memory area dest.  The memory areas must not overlap.
   Use memmove(3) if the memory areas do overlap.

   The difference between memcpy and strcpy is that strcpy stops when it
   encounters a NUL. You cannot see the difference with printf,
   because printf also stops at NUL.
*/

#include <string.h>
#include <stdio.h>
#include "libft.h"
#define TEST_FT ft_memcpy

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cpdest;
	unsigned char	*cpsrc;
	size_t			i;

	if (src == NULL && dest == NULL)
		return (dest);
	cpdest = (unsigned char *) dest;
	cpsrc = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		cpdest[i] = cpsrc[i];
		i++;
	}
	return (cpdest);
}
/*
int	main(void)
{
// Testing with a char string

	printf("\n");
	
	char	charsrc[7] = "ABCDEF";
	printf("src: %s\n", charsrc);

	char	chardst[7] = "abcdef";
	printf("dst: %s\n", chardst);

	printf("<<memcpy>>\n");
	TEST_FT(chardst, charsrc, 3);

	printf("src: %s\n", charsrc);
	printf("dst: %s\n\n", chardst);

// Testing with an int array

	int	i = 0;
	int	intsrc[3] = {1, 2, 3};
	printf("src: ");
	while (i <= 2)
	{
		printf("%d ", intsrc[i]);
		i++;
	}

	int	intdst[3] = {4, 5, 6};
	i = 0;
	printf("\ndst: ");
	while (i <= 2)
	{
		printf("%d ", intdst[i]);
		i++;
	}

	printf("\n<<memcpy>>\n");
	TEST_FT(intdst, intsrc, 5);

        i = 0;
        printf("src: ");
        while (i <= 2)
        {   
                printf("%d ", intsrc[i]);
                i++;
        }   

        i = 0;
        printf("\ndst: ");
        while (i <= 2)
        {   
                printf("%d ", intdst[i]);
                i++;
        }
	printf("\n\n");
	return (0);
}
*/
