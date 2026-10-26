/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:18:58 by hallison          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:15 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	finish_external(t_shell *shell, pid_t child_pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	if (waitpid(child_pid, &status, 0) == -1)
		return (ms_error_fail(shell, 1, "start_external()", "waitpid()"));
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		shell->last_exit_code = exit_code;
	}
	else if (WIFSIGNALED(status))
	{
		exit_code = 128 + WTERMSIG(status);
		write(1, "\n", 1);
	}
	sig_set_scope(shell, SIGSCOPE_INTERACTIVE);
	return (exit_code);
}

int	start_external(t_shell *shell, char *path, t_node *node, char **envp)
{
	pid_t	child_pid;

	if (access(path, F_OK) != 0)
		return (ms_error_external(127, 0, path));
	if (is_directory(path))
		return (ms_error_external(126, 1, path));
	if (access(path, X_OK) != 0)
		return (ms_error_external(126, 2, path));
	sig_set_scope(shell, SIGSCOPE_EXTERN);
	child_pid = fork();
	if (child_pid < 0)
		return (ms_error_fail(shell, 1, "start_external()", "fork()"));
	if (child_pid == 0)
	{
		sig_set_scope(shell, SIGSCOPE_EXEC);
		if (execve(path, node->args, envp) == -1)
			return (ms_error_external(126, 3, node->cmd));
	}
	return (finish_external(shell, child_pid));
}

t_hdoc	*find_ultimate_heredoc(t_node *node)
{
	t_hdoc	*ultimate_heredoc;
	int		i;

	i = 0;
	ultimate_heredoc = node->heredocs;
	while (ultimate_heredoc->next != NULL)
	{
		ultimate_heredoc = ultimate_heredoc->next;
		i++;
	}
	return (ultimate_heredoc);
}

int	start_external_hdoc(t_shell *shell, char *path, t_node *node, char **envp)
{
	t_hdoc	*ultimate_heredoc;
	char	*hdoc_path;
	int		file_fd;
	int		original_stdin;
	int		exit_code;

	ultimate_heredoc = find_ultimate_heredoc(node);
	hdoc_path = ultimate_heredoc->path;
	file_fd = open(hdoc_path, O_RDWR | O_CREAT, 0444);
	if (file_fd == -1)
		return (ms_error_fail(shell, 1, "start_external_hdoc()", "open()"));
	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
		return (ms_error_fail(shell, 1, "start_external_hdoc()", "dup()"));
	if (dup2(file_fd, STDIN_FILENO) == -1)
		return (ms_error_fail(shell, 1, "start_external_hdoc()", "dup2()"));
	exit_code = start_external(shell, path, node, envp);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		return (ms_error_fail(shell, 1, "start_external_hdoc()", "dup2()"));
	close(file_fd);
	close(original_stdin);
	return (exit_code);
}

int	handle_external(t_shell *shell, t_node *node, char **envp)
{
	char	*path;
	int		exit_code;

	if (node->cmd[0] == '\0' || (ft_strncmp(node->cmd, "..\0", 3) == 0))
		return (ms_error_cmd_not_found(shell, node->cmd));
	if (get_str_from_envp("PATH=", envp) == NULL)
		return (ms_error_no_such_file(shell, node->cmd));
	if (is_a_path(node->cmd) == true)
		path = ft_strdup(node->cmd);
	else
	{
		if (node->cmd[0] == '.' && node->cmd[1] == '\0')
			return (ms_error_dot_sourcing());
		path = get_path(shell, node->cmd, envp);
	}
	if (!path)
		return (ms_error_cmd_not_found(shell, node->cmd));
	if (node->heredocs != NULL)
		exit_code = start_external_hdoc(shell, path, node, envp);
	else
		exit_code = start_external(shell, path, node, envp);
	if (path)
		free(path);
	return (exit_code);
}
