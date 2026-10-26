/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:47 by hallison          #+#    #+#             */
/*   Updated: 2024/05/20 20:19:13 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created (using malloc(3)) to collect the
results from the successive applications of f.

s: The string on which to iterate.
f: The function to apply to each character.

The string created from the successive applications
of ’f’.
Returns NULL if the allocation fails.
*/

#include <stdio.h>
#include "libft.h"
/*
char	test_function(unsigned int i, char i_of_s)
{
	if (i == 0 && (i_of_s >= 'a' && i_of_s <= 'z'))
		i_of_s = i_of_s - ('a' - 'A');
	if (i != 0 && (i_of_s >= 'A' && i_of_s <= 'Z'))
		i_of_s = i_of_s + ('a' - 'A');
	return (i_of_s);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	size_t	newstr_len;
	size_t	i;

	newstr_len = ft_strlen(s);
	newstr = ft_calloc(newstr_len + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		newstr[i] = (*f)(i, s[i]);
		i++;
	}
	return (newstr);
}
/*
int	main(void)
{
	char	s[] = "ABCDEF";
	char (*function_ptr)(unsigned int, char);
	function_ptr = test_function;
	char	*x = ft_strmapi(s, function_ptr);
	printf("s = %s\n", s);
	printf("ft_strmapi(s, f) = %s\n", x); 
//	char	x = ft_strmapi(s);
}
*/
