/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:39:52 by hallison          #+#    #+#             */
/*   Updated: 2024/07/02 15:26:30 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 5

//size_t	ft_strlcat(char *dst, const char *src, size_t size);
//size_t	ft_strlen(const char *s);
//void	*ft_memcpy(void *dest, const void *src, size_t n); 
//char	*ft_strchr(const char *s, int c); 
//char	*ft_strdup(const char *s);

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cpdest;
	unsigned char	*cpsrc;
	size_t			i;

	if (src == NULL && dest == NULL)
		return (dest);
	cpdest = (unsigned char *) dest;
	cpsrc = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		cpdest[i] = cpsrc[i];
		i++;
	}
	return (cpdest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	if (src_len < size - dst_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*tempstring;
	char	x;

	x = (char)c;
	tempstring = (char *)s;
	i = 0;
	while (tempstring[i] != x && s[i] != '\0')
		i++;
	if (tempstring[i] == x)
		return (&tempstring[i]);
	else
		return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*newstr;
	size_t	stringlength;
	size_t	i;

	stringlength = ft_strlen((char *)s);
	newstr = (char *) malloc(stringlength + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < stringlength)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
//#endif
