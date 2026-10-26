/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:51:11 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:29:27 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"

t_node	*parse_tokens(t_shell *shell, t_token *start, t_token *end)
{
	t_node			*node;
	t_parse_state	state;

	if (!start || start == end)
		return (NULL);
	state.start = start;
	state.end = end;
	state.op = NULL;
	state.closing = NULL;
	if (state.start->type == T_OPEN_PAREN)
	{
		state.closing = parse_find_matching_paren(&state);
		if (state.closing && state.closing->next == end)
			return (parse_subshell(shell, &state));
	}
	state.op = parse_handle_precedence(&state);
	node = parse_init_node(shell);
	if (state.op)
		parse_handle_operators(shell, node, &state);
	else
		parse_handle_commands(shell, node, &state);
	return (node);
}

t_token	*parse_handle_precedence(t_parse_state *state)
{
	t_token			*curr;
	t_token			*max_prec_tok;
	t_precedence	best_prec;

	curr = state->start;
	max_prec_tok = NULL;
	best_prec = PREC_HIGHEST;
	while (curr && curr != state->end)
	{
		if (curr->type == T_OPEN_PAREN)
		{
			curr = parse_skip_paren(curr, state->end);
			if (!curr)
				break ;
			continue ;
		}
		parse_set_operator(curr, &max_prec_tok, &best_prec);
		curr = curr->next;
	}
	return (max_prec_tok);
}

t_node	*parse_init_node(t_shell *shell)
{
	t_node	*node;

	node = gc_malloc(shell, sizeof(t_node), &shell->exec_mem);
	ft_bzero(node, sizeof (*node));
	node->op_prec = PREC_HIGHEST;
	return (node);
}

void	parse_handle_operators(t_shell *shell, t_node *node, \
									t_parse_state *state)
{
	int		len;

	len = ft_strlen(state->op->value);
	node->cmd = gc_malloc(shell, len +1, &shell->exec_mem);
	ft_strcpy(node->cmd, state->op->value);
	node->op_prec = state->op->prec;
	node->args = NULL;
	node->left = parse_tokens(shell, state->start, state->op);
	node->right = parse_tokens(shell, state->op->next, state->end);
}

void	parse_handle_commands(t_shell *shell, t_node *node, \
									t_parse_state *state)
{
	t_token	*curr;

	curr = state->start;
	while (curr && curr != state->end)
	{
		if (curr->type == T_HEREDOC)
		{
			parse_handle_heredoc(shell, node, curr, state);
			if (shell->in_status == IN_ERROR)
				return ;
			curr = state->start;
			continue ;
		}
		if (curr->type == T_OUTPUT || curr->type == T_APPEND \
				|| curr->type == T_INPUT)
		{
			parse_handle_redir(shell, node, curr, state);
			if (shell->in_status == IN_ERROR)
				return ;
			curr = state->start;
			continue ;
		}
		curr = curr->next;
	}
	parse_fill_args(shell, node, state);
}
