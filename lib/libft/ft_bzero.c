/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:54:12 by hallison          #+#    #+#             */
/*   Updated: 2024/05/03 13:39:35 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   The  bzero()  function  erases  the  data  in the n bytes of the memory
   starting at the location pointed to by s, by writing zeros (bytes 
   containing '\0') to that area.

   void bzero(void *s, size_t n)
*/

#include <string.h>
#include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*cp;

	i = 0;
	cp = s;
	while (i < n)
	{
		cp[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{

// char * example
	char s[6] = "ABCDEF";
	printf("%s\n", s);
//	bzero(s, 1);
	ft_bzero(s, 1);
	printf("%s\n", s);

// int example
	int x = 9;
	int *j = &x;
	printf("%d\n", *j);
//	bzero(j, 1);
	ft_bzero(j, 1);
	printf("%d\n", *s);
	return (0);
}
*/
