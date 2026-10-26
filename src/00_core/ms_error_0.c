/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:02:22 by hallison          #+#    #+#             */
/*   Updated: 2025/06/27 18:36:53 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	ms_error_cmd_not_found(t_shell *shell, char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->last_exit_code = 127;
	return (127);
}

int	ms_error_no_such_file(t_shell *shell, char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	shell->last_exit_code = 127;
	return (127);
}

int	ms_error_dot_sourcing(void)
{
	ft_putstr_fd("minishell: dot sourcing not supported\n", 2);
	return (127);
}

int	ms_error_syntax(int code, char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	return (code);
}

/*
	ms_error_fail() prints error info in the unlikely case
	of system call or malloc failure ("char *call")
	within a given function (char *ft).
	
	shell->fatal is set to true, triggering exit at
	the end of execution loop.
*/

int	ms_error_fail(t_shell *shell, int code, char *ft, char *call)
{
	perror("Error");
	ft_putstr_fd(call, 2);
	ft_putstr_fd("failed in function: ", 2);
	ft_putstr_fd(ft, 2);
	ft_putstr_fd("\n", 2);
	shell->fatal = true;
	return (code);
}
