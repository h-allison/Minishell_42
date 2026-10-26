/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:47:20 by hallison          #+#    #+#             */
/*   Updated: 2025/04/14 14:47:30 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	exec_readend(t_node *node, char ***envp, int *pipefd, t_shell *shell)
{
	int	code;

	if (shell->prev_read_fd != -42)
	{
		if (dup2(shell->prev_read_fd, STDIN_FILENO) == -1)
			return (ms_error_fail(shell, 1, "exec_readend()", "dup2()"));
	}
	else
	{
		if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
			return (ms_error_fail(shell, 1, "exec_readend()", "dup2()"));
	}
	shell->prev_read_fd = pipefd[READ_END];
	if (close(pipefd[WRITE_END]) == -1 || close(pipefd[READ_END]) == -1)
	{
		perror("");
		return (-1);
	}
	if (set_arg_zero_code(node->cmd) == IS_EXIT)
		code = ms_clean_exit(shell, 0, false);
	else
		code = start_exec(node, envp, shell);
	exit(code);
}

int	exec_write_end(t_node *node, char ***envp, int *pipefd, t_shell *shell)
{
	int	code;

	if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
		return (ms_error_fail(shell, 1, "exec_write_end()", "dup2()"));
	if (close(pipefd[WRITE_END]) == -1 || close(pipefd[READ_END]) == -1)
		return (ms_error_fail(shell, 1, "exec_write_end()", "close()"));
	if (set_arg_zero_code(node->cmd) == IS_EXIT)
		code = ms_clean_exit(shell, 0, false);
	else
		code = start_exec(node, envp, shell);
	exit(code);
}

int	pipe_read_end(t_shell *shell, t_node *node, char ***envp, int *pipefd)
{
	pid_t	read_pid;
	int		status;
	int		exit_code;

	exit_code = 0;
	read_pid = fork();
	if (read_pid < 0)
		return (ms_error_fail(shell, 1, "pipe_read_end()", "fork()"));
	if (read_pid == 0)
		exit_code = exec_readend(node->right, envp, pipefd, shell);
	if (close(pipefd[READ_END]) == -1 || close(pipefd[WRITE_END]) == -1)
		return (ms_error_fail(shell, 1, "exec_read_end()", "close()"));
	if (waitpid(read_pid, &status, 0) == -1)
		return (ms_error_fail(shell, 1, "pipe_read_end()", "waitpid()"));
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	return (exit_code);
}

int	open_pipe(t_node *node, char ***envp, t_shell *shell)
{
	int		pipefd[2];
	pid_t	write_pid;
	int		exit_code;

	if (!node->right || !node->left)
		return (ms_error_syntax(2, "|"));
	exit_code = 0;
	if (pipe(pipefd) == -1)
		return (ms_error_fail(shell, 1, "open_pipe()", "pipe()"));
	write_pid = fork();
	if (write_pid < 0)
		return (ms_error_fail(shell, 1, "open_pipe()", "fork()"));
	if (write_pid == 0)
		exit_code = exec_write_end(node->left, envp, pipefd, shell);
	sig_set_scope(shell, SIGSCOPE_EXEC);
	exit_code = pipe_read_end(shell, node, envp, pipefd);
	waitpid(write_pid, NULL, 0);
	return (exit_code);
}
