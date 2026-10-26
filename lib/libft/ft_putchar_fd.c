/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:55:19 by hallison          #+#    #+#             */
/*   Updated: 2024/05/20 20:00:30 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Outputs the character ’c’ to the given file
descriptor.
*/
#include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
/*
int	main(void)
{
	char	c = 'X';
	int	fd = 1;
	ft_putchar_fd(c, fd);
//	write(1, &c, 1);
	return (0);
}
*/
