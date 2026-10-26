/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:54:43 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:29:31 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"

void	parse_handle_redir(t_shell *shell, t_node *node, \
						t_token *curr, t_parse_state *state)
{
	if (!parse_val_redir_token(shell, curr, state))
		return ;
	parse_add_redir(shell, node, curr->next->value, curr->type);
	parse_remove_redir_tokens(state, curr);
}

bool	parse_val_redir_token(t_shell *shell, t_token *curr, \
						t_parse_state *state)
{
	if (!curr->next || curr->next == state->end)
	{
		shell->in_status = IN_ERROR;
		return (false);
	}
	return (true);
}

void	parse_add_redir(t_shell *shell, t_node *node, char *redir_target, \
							t_token_type type)
{
	t_redir	*new_redir;
	t_redir	*curr;

	if (!redir_target)
		return ;
	new_redir = gc_malloc(shell, sizeof(t_redir), &shell->exec_mem);
	new_redir->target = gc_malloc(shell, ft_strlen(redir_target) + 1, \
							&shell->exec_mem);
	ft_strlcpy(new_redir->target, redir_target, ft_strlen(redir_target) + 1);
	new_redir->type = type;
	new_redir->append = (type == T_APPEND);
	new_redir->next = NULL;
	if (!node->redirections)
		node->redirections = new_redir;
	else
	{
		curr = node->redirections;
		while (curr->next)
			curr = curr->next;
		curr->next = new_redir;
	}
}

void	parse_remove_redir_tokens(t_parse_state *state, t_token *redir)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*after;

	prev = NULL;
	curr = state->start;
	while (curr && curr != redir)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr || !curr->next)
		return ;
	after = curr->next->next;
	if (prev)
		prev->next = after;
	else
		state->start = after;
}

void	parse_handle_heredoc(t_shell *shell, t_node *node, \
							t_token *curr, t_parse_state *state)
{
	if (!parse_val_redir_token(shell, curr, state))
		return ;
	heredoc_add_to_node(shell, node, curr->next->value, curr->next->quoted);
	if (shell->in_status == IN_ERROR)
		heredoc_unlink_all(node);
	else
		parse_remove_redir_tokens(state, curr);
}
