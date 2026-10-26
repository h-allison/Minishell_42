/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:46:05 by hallison          #+#    #+#             */
/*   Updated: 2025/06/27 19:55:53 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	ms_clean_exit(t_shell *shell, int exit_code, bool print)
{
	if (print == true)
		printf("exit\n");
	gc_cleanup_shell(shell);
	exit(exit_code);
}

int	ms_exit(t_shell *shell, t_node *node)
{
	printf("exit\n");
	if (node->args && node->args[1])
	{
		if (!ft_isnumber(node->args[1]))
			ms_error_exit(shell, 2, node->args[1]);
		else if (node->args[2])
			ms_error_exit(shell, 1, NULL);
		else if (!ft_is_valid_int_range(node->args[1]))
			ms_error_exit(shell, 3, node->args[1]);
		else
			shell->last_exit_code = ft_atoi(node->args[1]) % 256;
	}
	ms_clean_exit(shell, shell->last_exit_code, false);
	exit(shell->last_exit_code);
	return (0);
}

static int	ft_get_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

bool	ft_is_valid_int_range(char *str)
{
	int		sign;
	long	val;

	if (!str || !*str)
		return (false);
	sign = ft_get_sign(&str);
	if (!*str)
		return (false);
	val = 0;
	while (*str >= '0' && *str <= '9')
	{
		val = val * 10 + (*str - '0');
		if ((sign == 1 && val > INT_MAX) \
			|| (sign == -1 && val > -(long)INT_MIN))
			return (false);
		str++;
	}
	return (*str == '\0');
}
