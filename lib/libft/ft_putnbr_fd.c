/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:55:55 by hallison          #+#    #+#             */
/*   Updated: 2024/05/22 23:56:12 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Outputs the integer ’n’ to the given file
descriptor.

INT_MIN needs to be hard coded so arithmetic doesn't turn it positive.

INT_MAX I am hard coding just for good measure -- not necessary?
*/
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
#include <limits.h>

int	get_n_len(int n)
{
	int	int_len;

	int_len = 0;
	while (n != 0)
	{
		n = n / 10;
		int_len++;
	}
	return (int_len);
}

void	unsigned_n_to_string(char *nmbrstr, int n)
{
	int	i;
	int	len;

	len = get_n_len(n);
	i = len - 1;
	while (n != 0)
	{
		nmbrstr[i] = ((n % 10) + 48);
		n = n / 10;
		i--;
	}
	nmbrstr[len] = '\0';
	return ;
}

int	ft_putminmax_fd(int n, int fd)
{
	if (n == 2147483647)
	{
		write(fd, "2147483647", 10);
		return (0);
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (0);
	}
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nmbrstr[10];

	if (!ft_putminmax_fd(n, fd))
		return ;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	unsigned_n_to_string(nmbrstr, n);
	ft_putstr_fd(nmbrstr, fd);
	return ;
}
/*
int	main(void)
{
	int	n = 2147483647;
	int	fd = 1;
	ft_putnbr_fd(n, fd);	
	return (0);
}
*/
