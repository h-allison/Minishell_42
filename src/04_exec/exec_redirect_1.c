/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:35:17 by hallison          #+#    #+#             */
/*   Updated: 2025/06/20 13:35:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

/*
	replace_stdin_stdout():
	- makes STDIN_FILENO an alias for input fd, if applicable
	- makes STDOUT_FILENO an alias for, if applicable
	Returns 0 on success and 1 on error
*/

int	replace_stdin_stdout(int in_file_fd, int out_file_fd)
{
	if (in_file_fd > 0)
	{
		if (dup2(in_file_fd, STDIN_FILENO) == -1)
			return (1);
	}
	if (out_file_fd > 0)
	{
		if (dup2(out_file_fd, STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

int	restore_stdin_stdout(int original_in, int original_out)
{
	if (dup2(original_in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(original_out, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int	dup_original_fds(int *original_stdin, int *original_stdout)
{
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
		return (1);
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdout == -1)
		return (1);
	return (0);
}

int	close_fd_dups(t_shell *shell, int fd_1, int fd_2)
{
	if (close (fd_1) == -1)
		return (ms_error_fail(shell, 1, "close_fd_dups()", "close()"));
	if (close (fd_2) == -1)
		return (ms_error_fail(shell, 1, "close_fd_dups()", "close()"));
	return (0);
}

int	exec_redir_exit(t_node *node, t_shell *shell)
{
	int	file_fd;

	file_fd = open_all_for_output(node);
	if (file_fd < 0)
		return (ms_error_fail(shell, 1, "open_all_for_input()", "open()"));
	if (file_fd > STDIN_FILENO)
		close(file_fd);
	return (ms_exit(shell, node));
}
