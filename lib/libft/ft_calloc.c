/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:53:01 by hallison          #+#    #+#             */
/*   Updated: 2024/05/23 11:55:36 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The calloc() function allocates memory for an array of  nmemb  elements
       of  size bytes each and returns a pointer to the allocated memory.  The
       memory is set to zero.  If nmemb or size is 0,  then  calloc()  returns
       either  NULL,  or a unique pointer value that can later be successfully
       passed to free().  If the multiplication of nmemb and size would result
       in  integer  overflow, then calloc() returns an error.  By contrast, an
       integer overflow would not be detected in the following  call  to  mal‐
       loc(),  with the result that an incorrectly sized block of memory would
       be allocated:

           malloc(nmemb * size);
	
	Question: I originally had a condition that
	if (nmemb == 0 || size == 0)
		return (NULL);
	However, this does not pass francinette.
	Why should we let the function return a pointer to nothing?
	Wouldn't it be better to return NULL in this case?

	
	Also, why do we need to include a "protective" NULL return
	if memory allocation fails? Wouldn't it be better to write this
	into whatever the function is that calls calloc, if desired?
	Would it not be better to let the program crash, in many cases?
*/

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define TEST_FT ft_calloc

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*memorypointer;
	size_t			memorysize;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size >= SIZE_MAX / nmemb)
		return (NULL);
	memorysize = nmemb * size;
	memorypointer = malloc(memorysize);
	if (!memorypointer)
		return (NULL);
	i = 0;
	while (i < memorysize)
	{
		memorypointer[i] = 0;
		i++;
	}
	return (memorypointer);
}
/*
int	main(void)
{
	//Testing char*
	char	*string;
	string = (char *)TEST_FT(4, sizeof(char));
	if (string == NULL)
	{
		printf("ERROR. Memory allocation failed.\n");
	}
	if (string != NULL)
	{
		printf("Char* test memory allocated\n");
	}

	//Testing int*
	int	*array;
	size_t	i;
	size_t	nmemb;

	i = 0;
	nmemb = 0;
	array = (int *)TEST_FT(nmemb, sizeof(int));
	if (array == NULL)
	{
		printf("ERROR. Memory allocation failed. \n");
	}
	if (array[i] == 0)
		printf("Int* test memory allocated.\nThe first member of Array = 0.\n");
	if (array != NULL)
	{
		while (i < nmemb)
		{
			printf("%i\n", array[i]);
			i++;
		}
	}
	return(0);
}
*/
