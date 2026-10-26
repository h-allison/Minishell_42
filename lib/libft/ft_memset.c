/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:47:53 by hallison          #+#    #+#             */
/*   Updated: 2024/05/05 17:37:46 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The memset() function fills the first n bytes of the memory area
pointed to by s with the constant byte c.
The memset() function returns a pointer to the memory area s.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*cp;
	size_t				i;

	cp = s;
	i = 0;
	while (i < n)
	{
		cp[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

/* Main to test char string */
/*
int	main(void)
{
	char	string[7] = "123456";
	memset (string, 'x', 3);
//	ft_memset(string, 'x', 3);
	printf("%s\n", string);
	return(0);
}
*/
/* Main to test int array */
/*
int     main(void)
{

        int     array[6] = {1, 2, 3, 4, 5, 6};
	int	i;
	i = 0;
        while (i < 6)
        {
                printf("%d", array[i]);
                i++;
        }
//	memset (array, '6', 4);
//	ft_memset(array, 'x', 4);

	i = 0;
	printf("%zu\n", (sizeof(array)));
	while (i < 6)
	{
		printf("%d", array[i]);
		i++;
	}
	return (0);
}
*/
/*Main to test int */
/*
int	main (void)
{
	int value;
	int *ptr = &value;
	*ptr = 42;
	printf("%d\n", value);
//	ft_memset(ptr, 24, 4);
	memset(ptr, 24, 4);
	printf("%d\n", value);
	return (0);
}
*/
