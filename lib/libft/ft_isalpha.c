/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:03:36 by hallison          #+#    #+#             */
/*   Updated: 2024/05/13 14:20:47 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
isalpha() checks  for an alphabetic character; in the standard "C" locale,
it is equivalent to (isupper(c) ||  islower(c)).

In  some  locales, there may be additional characters for which isalpha()
is true — letters which are neither uppercase nor lowercase.

Even though, isalpha() takes integer as an argument, character is passed to
isalpha() function.

Internally, the character is converted into the integer value corresponding
to its ASCII value when passed.

My tests show that isalpha() returns 1024 when the characters is alpha,
and 0 when it is not. From reading online, 1024 seems to be specific to my
system, but 0 for non-alpha character is universal.

My tests also show that testing with extended ASCII characters results in
a compiler error. (character too large for enclosing character literal type")
*/

#include "libft.h"
#include <ctype.h>
#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1024);
	else
		return (0);
}

/*
int	main(void)
{
	int	c;

	c = 'Z';
	printf("%i\n", isalpha(c));
	printf("%i\n", ft_isalpha(c));
	return (0);
}
*/
