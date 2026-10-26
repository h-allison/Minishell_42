/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putend1_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:55:37 by hallison          #+#    #+#             */
/*   Updated: 2024/05/20 20:34:19 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Outputs the string ’s’ to the given file descriptor
followed by a newline.
*/
#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	char	s[] = "String followed by newline.";
	int	fd = 1;
	ft_putend1_fd(s, fd);
	return (0);
}
*/
