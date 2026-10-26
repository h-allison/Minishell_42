/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:19:39 by hallison          #+#    #+#             */
/*   Updated: 2025/04/07 10:55:40 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	open_all_for_input(t_node *node)
{
	t_redir	*file;
	int		file_fd;

	file = node->redirections;
	while (file != NULL && file->type != T_INPUT)
		file = file->next;
	if (file == NULL)
		return (0);
	file_fd = open(file->target, O_RDONLY);
	if (file_fd == -1)
		return (ms_error_redirect(file->target));
	while (file->next != NULL)
	{
		file = file->next;
		if (file->type == T_INPUT)
		{
			close(file_fd);
			file_fd = open(file->target, O_RDONLY);
			if (file_fd == -1)
				return (ms_error_redirect(file->target));
		}
	}
	return (file_fd);
}

int	open_output_file(t_redir *file)
{
	int		fd;
	char	*file_path;

	file_path = file->target;
	if (file->type == T_OUTPUT)
		fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (file->type == T_APPEND)
		fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = -2;
	return (fd);
}

int	open_all_for_output(t_node *node)
{
	t_redir	*file;
	int		file_fd;

	file = node->redirections;
	while (file != NULL && file->type != T_APPEND && file->type != T_OUTPUT)
		file = file->next;
	if (file == NULL)
		return (0);
	file_fd = open_output_file(file);
	if (file_fd < 0)
		return (ms_error_redirect(file->target));
	while (file->next != NULL)
	{
		file = file->next;
		if (file->type == T_APPEND || file->type == T_OUTPUT)
		{
			close(file_fd);
			file_fd = open_output_file(file);
			if (file_fd < 0)
				return (ms_error_redirect(file->target));
		}
	}
	return (file_fd);
}

int	open_all_fds(t_node *node, int *file_fd)
{
	file_fd[0] = open_all_for_input(node);
	if (file_fd[0] < 0)
		return (1);
	file_fd[1] = open_all_for_output(node);
	if (file_fd[1] < 0)
	{
		if (file_fd[0] > STDIN_FILENO)
			close (file_fd[0]);
		return (1);
	}
	return (0);
}
