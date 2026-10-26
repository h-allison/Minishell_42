/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:01 by hallison          #+#    #+#             */
/*   Updated: 2025/03/24 17:14:30 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_realloc(char *ptr, size_t size)
{
	char	*new_ptr;
	size_t	i;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < size && ptr[i] != '\0')
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}
