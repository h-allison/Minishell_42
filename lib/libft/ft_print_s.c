/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:42:58 by hallison          #+#    #+#             */
/*   Updated: 2024/08/12 12:29:57 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   Writes a string.
*/

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	ft_print_s(char	*arg)
{
	size_t	count;

	if (arg == NULL)
		arg = "(null)";
	count = ft_strlen(arg);
	write(1, arg, count);
	return (count);
}
