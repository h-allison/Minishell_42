/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ops_paren.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:05:49 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/23 17:07:27 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"

void	parse_set_operator(t_token *curr, t_token **best, t_precedence *prec)
{
	if ((curr->type == T_PIPE || curr->type == T_AND || \
			curr->type == T_OR) && curr->prec >= *prec)
	{
		*best = curr;
		*prec = curr->prec;
	}
}

t_node	*parse_subshell(t_shell *shell, t_parse_state *state)
{
	t_node	*node;

	node = parse_init_node(shell);
	node->op_prec = PREC_SUBSHELL;
	node->cmd = NULL;
	node->args = NULL;
	node->left = parse_tokens(shell, state->start->next, state->closing);
	node->right = NULL;
	return (node);
}

t_token	*parse_skip_paren(t_token *curr, t_token *end)
{
	int	depth;

	depth = 1;
	curr = curr->next;
	while (curr && curr != end && depth)
	{
		if (curr->type == T_OPEN_PAREN)
			depth++;
		else if (curr->type == T_CLOSE_PAREN)
			depth--;
		curr = curr->next;
	}
	return (curr);
}

t_token	*parse_find_matching_paren(t_parse_state *state)
{
	int		depth;
	t_token	*tok;

	depth = 0;
	tok = state->start;
	while (tok && tok != state->end)
	{
		if (tok->type == T_OPEN_PAREN || tok->type == T_CMDSUB)
			depth++;
		else if (tok->type == T_CLOSE_PAREN || tok->type == T_CMDSUB)
		{
			depth--;
			if (depth == 0)
				return (tok);
		}
		tok = tok->next;
	}
	return (NULL);
}
