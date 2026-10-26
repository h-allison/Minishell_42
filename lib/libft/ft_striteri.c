/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:55:08 by hallison          #+#    #+#             */
/*   Updated: 2024/05/20 18:05:11 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
*/
#include "libft.h"
#include <stdio.h>
/*
void	ft_dir_name_format(unsigned int i, char* str)
{
	if (i > 1)
	{
		if (*str == ' ')
			*str = '_';
		if (*str >= 'a' && *str <= 'z')
			*str = *str - ('a' - 'A');
	}
	return;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
	return ;
}
/*
int	main(void)
{
	char s[] = "_a b c";
	void (*function_ptr)(unsigned int, char*);

	function_ptr = ft_dir_name_format;
	printf("s = %s\n", s);
	printf("ft_striteri(s, i)\n");
	ft_striteri(s, function_ptr);
	printf("s = %s\n", s);
}
*/
