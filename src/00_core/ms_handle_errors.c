/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:56:22 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:55:06 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_defs.h"

const char	**ms_error_table(void)
{
	static const char	*msgs[] = {
		"memory allocation failed",
		"heredoc initialization failed",
		"invalid token",
		"no support for backgrounding",
		"no support for that feature",
		"command not found",
		"syntax error",
		"could not open file",
		"execution failed",
		"too many arguments",
		"too few arguments",
		"unknown error"
	};

	return (msgs);
}

const char	*ms_get_error_msg(t_ms_err err)
{
	const char	**msgs;

	msgs = ms_error_table();
	if (err < 0 || err > ERR_UNKNOWN)
		err = ERR_UNKNOWN;
	return (msgs[err]);
}

void	ms_error_msg(t_shell *shell, int code, char *spot, t_ms_err err)
{
	char	*msg;

	msg = (char *)ms_get_error_msg(err);
	ft_putstr_fd("minishell: ", 2);
	if (spot)
	{
		ft_putstr_fd(spot, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	shell->last_exit_code = code;
}
