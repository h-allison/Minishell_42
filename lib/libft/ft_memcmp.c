/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:52:27 by hallison          #+#    #+#             */
/*   Updated: 2024/05/09 15:22:36 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
  The  memcmp()  function compares the first n bytes (each interpreted as
  unsigned char) of the memory areas s1 and s2.

  The memcmp() function returns an integer less than, equal to, or greater
  than zero if  the  first  n bytes  of s1 is found, respectively,
  to be less than, to match, or be greater than the first n bytes of s2.

  For a nonzero return value, the sign is determined by the sign of the
  difference between  the  first pair of bytes (interpreted as unsigned char)
  that differ in s1 and s2.

  If n is zero, the return value is zero.

  Do  not  use  memcmp() to compare security critical data,
  such as cryptographic secrets, because the required CPU time
  depends on the number of equal bytes.
*/

#include <string.h>
#include <stdio.h>
#define TEST_FT memcmp
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_charptr;
	unsigned char	*s2_charptr;
	size_t			i;

	s1_charptr = (unsigned char *)s1;
	s2_charptr = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_charptr[i] != s2_charptr[i])
			return (s1_charptr[i] - s2_charptr[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char mem_area_1 [] = "abc";
	char mem_area_2 [] = "abc";
//	int	mem_area_3 [] = {1, 2, 3, 4};
//	int	mem_area_4 [] = {5};
	printf("%d\n", ft_memcmp(mem_area_1, mem_area_2, 7));
	printf("%d\n", ft_memcmp(mem_area_1, mem_area_2, 7));
	return(0);
}
*/
