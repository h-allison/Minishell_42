/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:19 by hallison          #+#    #+#             */
/*   Updated: 2024/05/23 00:07:26 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_split() allocates (with malloc(3)) and returns an array of strings
	obtained by splitting ’s’ using the character ’c’ as a delimiter.
	The array must end with a NULL pointer.

	s = The string to be split.
	c = The delimiter character.

	The array of new strings resulting from the split.
	NULL if the allocation fails.

	cc -Wall -Wextra -Werror ft_split.c ft_strchr.c ft_strtrim.c
	ft_strdup.c ft_strlcpy.c ft_memcpy.c ft_strlen.c ft_calloc.c

	If nothing to split, should return split_string_array[0] = (null)
*/
// #include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

static size_t	get_array_len(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	count = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

void	strings_allocate(char **array, char *s_mod, size_t array_len, size_t z)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < z && i < array_len)
	{
		if (s_mod[j] != '\0')
		{
			array[i] = ft_strdup(s_mod + j);
			i++;
			while (s_mod[j] != '\0')
				j++;
		}
		else
			j++;
	}
}

void	array_allocate(char **array, const char *s, char c, size_t array_len)
{
	size_t	i;
	size_t	s_len;
	char	*s_mod;

	s_mod = ft_strdup(s);
	if (!s_mod)
		return ;
	s_len = ft_strlen(s_mod);
	i = 0;
	while (i < s_len)
	{
		if (s_mod[i] == c)
			s_mod[i] = '\0';
		i++;
	}
	strings_allocate(array, s_mod, array_len, s_len);
	free (s_mod);
}

int	check_free(char **split_array, size_t array_len)
{
	size_t	i;

	i = 0;
	while (i < array_len)
	{
		if (!split_array[i])
		{
			i = 0;
			while (i < array_len)
			{
				free (split_array[i]);
				i++;
			}
			free (split_array);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split_array;
	size_t	array_len;

	if (!s)
		return (NULL);
	array_len = get_array_len(s, c);
	split_array = ft_calloc(array_len + 1, sizeof(char **));
	if (split_array == NULL)
		return (NULL);
	array_allocate(split_array, s, c, array_len);
	if (!check_free(split_array, array_len))
		return (NULL);
	return (split_array);
}

/*
int	main(void)
{
	char	s[] = "xAB";
	char	c = 'x';
	size_t	i;
	printf("\nstring: %s\n", s);
	printf("delimiter char: %c\n", c);
		char**  split_string_array = ft_split(s, c);
	i = 0;
	while(i < 3)
	{
		printf("split_string_array[%zu] = %s\n", i, split_string_array[i]);
		i++;
	}
	return (0);
}
*/
