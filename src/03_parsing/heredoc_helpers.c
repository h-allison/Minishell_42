/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:26:23 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:44:15 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"
#include <unistd.h>

char	*heredoc_get_path(t_shell *shell)
{
	char	*num;
	char	*filename;
	char	*prefix;
	char	*path;

	num = ft_itoa(shell->heredoc_counter++);
	if (!num)
		return (ms_error_msg(shell, 1, "heredoc_get_path/counter", \
											ERR_MALLOC_FAIL), NULL);
	filename = ft_strjoin(".heredoc_", num);
	free(num);
	if (!filename)
		return (ms_error_msg(shell, 1, "heredoc_get_path/filename", \
											ERR_MALLOC_FAIL), NULL);
	if (access("/tmp", W_OK) == 0)
		prefix = "/tmp/";
	else
		prefix = "./";
	heredoc_assemble_path(shell, filename, &path, prefix);
	free(filename);
	return (path);
}

void	heredoc_assemble_path(t_shell *shell, char *filename, \
									char **path, char *prefix)
{
	size_t	len;

	len = ft_strlen(prefix) + ft_strlen(filename) + 1;
	*path = gc_malloc(shell, len, &shell->exec_mem);
	ft_strlcpy(*path, prefix, len);
	ft_strlcat(*path, filename, len);
	return ;
}

char	*heredoc_remove_outer_quotes(t_shell *shell, char *str, int quotes)
{
	char	*clean;
	size_t	len;

	if (quotes != 1 && quotes != 2)
		return (str);
	len = ft_strlen(str);
	if (len < 2 || str[0] != str[len - 1])
		return (str);
	if (str[0] != '\'' && str[0] != '\"')
		return (str);
	clean = gc_malloc (shell, len - 1, &shell->exec_mem);
	ft_strlcpy(clean, str + 1, len - 1);
	return (clean);
}

void	heredoc_unlink_all(t_node *node)
{
	t_hdoc	*curr;

	if (!node)
		return ;
	curr = node->heredocs;
	while (curr)
	{
		if (curr->path)
		{
			unlink(curr->path);
			curr->path = NULL;
		}
		curr = curr->next;
	}
	heredoc_unlink_all(node->left);
	heredoc_unlink_all(node->right);
}
