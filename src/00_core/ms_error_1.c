/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:02:22 by hallison          #+#    #+#             */
/*   Updated: 2025/06/27 18:36:53 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	ms_error_external(int code, int why, char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (why == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (why == 1)
		ft_putstr_fd(": Is a directory\n", 2);
	else if (why == 2)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (why == 3)
		perror("");
	return (code);
}

/*
	ms_error_redirect() is specifc to redirection helper functions
	
	IMPORTANT: Does NOT return an exit code.
	This error function is called only when open() fails.
	Like read(), it returns -1, triggering a return from
	exec_redir with exit code 1.
*/

int	ms_error_redirect(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	perror(" ");
	return (-1);
}

int	ms_error_cd(int type, char *s)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	if (type == 0)
		ft_putstr_fd("Error\n", 2);
	if (type == 1)
		ft_putstr_fd("too many arguments\n", 2);
	if (type == 2)
		perror("");
	if (type == 3)
		ft_putstr_fd("Not a directory\n", 2);
	if (type == 4)
		perror("");
	return (1);
}

int	ms_error_exit(t_shell *shell, int code, char *s)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (code == 1)
	{
		ft_putstr_fd("too many arguments\n", 2);
		shell->last_exit_code = 1;
	}
	if (code == 2)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->last_exit_code = 2;
	}
	if (code == 3)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numerical value needs to be valid int\n", 2);
		shell->last_exit_code = 2;
	}
	return (1);
}

int	ms_error_export(t_shell *shell, int code, char *s)
{
	if (code == 2)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		shell->last_exit_code = 2;
	}
	return (1);
}
