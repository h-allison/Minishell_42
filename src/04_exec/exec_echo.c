/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:34:11 by hallison          #+#    #+#             */
/*   Updated: 2025/04/09 18:34:24 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

void	no_new_line(char *argument)
{
	size_t	i;

	i = 0;
	while (argument[i] != '\0')
		i++;
	write(1, argument, i);
	return ;
}

int	is_no_newline_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_no_newline(t_node *node)
{
	int	i;

	i = 1;
	while (is_no_newline_flag(node->args[i]) == 1)
		i++;
	while (node->args[i] != NULL)
	{
		no_new_line(node->args[i]);
		if (node->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	exec_echo(t_node *node)
{
	int	i;

	if (node->args[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	if (is_no_newline_flag(node->args[i]) == 1)
		echo_no_newline(node);
	else
	{
		while (node->args[i] != NULL)
		{
			write(1, node->args[i], ft_strlen(node->args[i]));
			if (node->args[i + 1] != NULL)
				write(1, " ", 1);
			else
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
