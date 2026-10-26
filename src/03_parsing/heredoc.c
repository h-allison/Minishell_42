/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:40:38 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 15:00:30 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"
#include "ms_input.h"

void	heredoc_init(t_shell *shell, t_hdoc *heredoc)
{
	int		fd;

	if (!heredoc || !heredoc->delim || !heredoc->path)
	{
		ms_error_msg(shell, 1, "heredoc", ERR_HEREDOC_INIT);
		return ;
	}
	if (!heredoc->path)
	{
		ms_error_msg(shell, 1, "heredoc", ERR_OPEN_FAIL);
		return ;
	}
	fd = open(heredoc->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ms_error_msg(shell, 1, heredoc->path, ERR_OPEN_FAIL);
		return ;
	}
	heredoc_write_to_file(shell, fd, heredoc);
	close(fd);
	return ;
}

void	heredoc_add_to_node(t_shell *shell, t_node *node, \
									char *delim, int quoted)
{
	t_hdoc	*new;
	t_hdoc	*last;

	new = gc_malloc(shell, sizeof(t_hdoc), &shell->exec_mem);
	new->delim = delim;
	new->quotes = quoted;
	new->path = heredoc_get_path(shell);
	if (!new->path)
	{
		ms_error_msg(shell, 1, "heredoc", ERR_OPEN_FAIL);
		return ;
	}
	new->next = NULL;
	if (!node->heredocs)
		node->heredocs = new;
	else
	{
		last = node->heredocs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	heredoc_write_to_file(t_shell *shell, int fd, t_hdoc *heredoc)
{
	char	*line;

	sig_set_scope(shell, SIGSCOPE_HEREDOC);
	while (1)
	{
		shell->prompt = prompt_alt(shell);
		line = readline(shell->prompt);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc ended with ctrl-D\n", 2);
			break ;
		}
		if (ft_strcmp(line, heredoc->delim) == 0)
		{
			free(line);
			break ;
		}
		if (heredoc->quotes == 0)
			line = tok_expand_vars(shell, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		if (line)
			free(line);
	}
	return ;
}

void	heredoc_fork(t_shell *shell, t_hdoc *heredoc)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ms_error_msg(shell, 1, "heredoc", ERR_EXEC_FAIL);
		ms_clean_exit(shell, 1, true);
	}
	else if (pid == 0)
	{
		sig_set_scope(shell, SIGSCOPE_HEREDOC);
		heredoc_init(shell, heredoc);
		exit(0);
	}
	sig_set_scope(shell, SIGSCOPE_EXTERN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->last_exit_code = WEXITSTATUS(status);
		if (shell->last_exit_code == 130)
			shell->in_status = IN_ERROR;
		else
			shell->in_status = IN_COMPLETE;
	}
}

void	heredoc_start(t_shell *shell, t_node *node)
{
	t_hdoc	*curr;

	if (!node || shell->in_status == IN_ERROR)
		return ;
	curr = node->heredocs;
	while (curr && shell->in_status != IN_ERROR)
	{
		heredoc_fork(shell, curr);
		sig_set_scope(shell, SIGSCOPE_INTERACTIVE);
		curr = curr->next;
	}
	heredoc_start(shell, node->left);
	heredoc_start(shell, node->right);
}
