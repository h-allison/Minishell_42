/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:44:00 by hallison          #+#    #+#             */
/*   Updated: 2025/06/20 13:31:36 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	exec_redir_command(t_shell *shell, t_node *node, char ***envp)
{
	int		exit_code;
	int		arg_zero;

	if (node->cmd == NULL || node->cmd[0] == '\0')
		return (0);
	arg_zero = set_arg_zero_code(node->cmd);
	if (arg_zero == IS_PIPE)
		exit_code = open_pipe(node, envp, shell);
	else if (arg_zero > 0)
		exit_code = handle_built_in(node, envp, shell);
	else
		exit_code = handle_external(shell, node, *envp);
	return (exit_code);
}

/*
	exec_redir() handles '>' '>>' and '<'
	
	file_fd[0] = input file fd, replacing stdin
	file_fd[1] = output file fd, replacing stdout
*/

int	exec_redir(t_node *node, char ***envp, t_shell *shell)
{
	int	file_fd	[2];
	int	original_stdin;
	int	original_stdout;
	int	exit_code;

	if (node->arg_zero == IS_EXIT)
		return (exec_redir_exit(node, shell));
	exit_code = (open_all_fds(node, file_fd) != 0);
	if (exit_code != 0)
		return (exit_code);
	if (dup_original_fds(&original_stdin, &original_stdout) != 0)
		return (ms_error_fail(shell, 1, "dup_original_fds()", "dup()"));
	if (replace_stdin_stdout(file_fd[0], file_fd[1]) != 0)
		return (ms_error_fail(shell, 1, "replace_stdin_stdout()", "dup2()"));
	exit_code = exec_redir_command(shell, node, envp);
	if (restore_stdin_stdout(original_stdin, original_stdout) != 0)
		return (ms_error_fail(shell, 1, "restore_stdin_stdout", "dup2()"));
	close_fd_dups(shell, original_stdin, original_stdout);
	if (file_fd[0] > STDIN_FILENO)
		close(file_fd[0]);
	if (file_fd[1] > STDOUT_FILENO)
		close(file_fd[1]);
	return (exit_code);
}
