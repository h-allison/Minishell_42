/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:13 by hallison          #+#    #+#             */
/*   Updated: 2024/05/15 12:22:07 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
	ft_strtrim() allocates with malloc(3) and returns a copy of 's1'
	with the characters specified in 'set' removd from the beginning
	and the end of the string.

	s1 = The string to be trimmed.
	set = The reference set of characters to trim.

	Return value = the trimmed string, or NULL if allocation fails.

	I've included this condition based only on francinette tests:
        
		if ((trim_start) == ft_strlen(s1))
                	return (ft_strdup(""))

	Would it not be better to return NULL and allow it to crash?
*/

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

size_t	ft_find_trim_index(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

size_t	ft_find_trim_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*returnstring;
	size_t	trim_start;
	size_t	trim_end;
	size_t	trim_len;

	trim_len = 0;
	trim_start = ft_find_trim_index(s1, set);
	if ((trim_start) == ft_strlen(s1))
		return (ft_strdup(""));
	trim_end = ft_find_trim_end(s1, set);
	trim_len = trim_end - trim_start + 1;
	returnstring = malloc((trim_len + 1) * sizeof(char));
	if (returnstring == NULL)
		return (NULL);
	ft_strlcpy(returnstring, s1 + trim_start, trim_len + 1);
	return (returnstring);
}
/*
int	main(void)
{
	char const	*s1 = "  ";
	char const	set[] = "   ";
        DEBUG_PRINTF("DEBUG MODE ON\n--------------\n\n");
	DEBUG_PRINTF("s1 = %s\n", s1);
	DEBUG_PRINTF("set = %s\n", set);
	char	*trimmed_s = ft_strtrim(s1, set);

	printf("\nOUTPUT:%s\n", trimmed_s);
	printf("Trimmed length: %zu\n", ft_strlen(trimmed_s));
	return (0);
}
*/
