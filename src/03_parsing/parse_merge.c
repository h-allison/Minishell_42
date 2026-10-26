/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:02:18 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:41:24 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"

static void	parse_finalize_args_node(t_node *node, int i, t_parse_state *state)
{
	node->args[i] = NULL;
	node->cmd = node->args[0];
	node->quotes = state->start->quoted;
	node->op_prec = PREC_HIGHEST;
	node->left = NULL;
	node->right = NULL;
}

void	parse_fill_args(t_shell *shell, t_node *node, t_parse_state *state)
{
	t_token	*curr;
	int		arg_count;
	int		i;

	if (!state->start || state->start == state->end)
		return ;
	curr = state->start;
	arg_count = 0;
	while (curr && curr != state->end)
	{
		arg_count++;
		while (curr->merge && curr->next && curr->next != state->end)
			curr = curr->next;
		curr = curr->next;
	}
	node->args = gc_malloc(shell, sizeof(char *) * (arg_count + 1), \
													&shell->exec_mem);
	curr = state->start;
	i = 0;
	while (curr && curr != state->end)
		node->args[i++] = parse_merge_tokens(shell, &curr, state->end);
	parse_finalize_args_node(node, i, state);
}

char	*parse_merge_tokens(t_shell *shell, t_token **curr, t_token *end)
{
	t_token	*tok;
	t_token	*prev;
	int		len;
	char	*buf;

	len = parse_calc_merged_len(*curr, end);
	buf = gc_malloc(shell, len + 1, &shell->exec_mem);
	buf[0] = '\0';
	tok = *curr;
	prev = NULL;
	ft_strlcat(buf, tok->value, len + 1);
	prev = tok;
	tok = tok->next;
	while (tok && tok != end && prev && prev->merge)
	{
		ft_strlcat(buf, tok->value, len + 1);
		prev = tok;
		tok = tok->next;
	}
	*curr = tok;
	return (buf);
}

int	parse_calc_merged_len(t_token *start, t_token *end)
{
	t_token	*tok;
	t_token	*prev;
	int		len;

	len = 0;
	tok = start;
	prev = NULL;
	len += ft_strlen(tok->value);
	prev = tok;
	tok = tok->next;
	while (tok && tok != end && prev && prev->merge)
	{
		len += ft_strlen(tok->value);
		prev = tok;
		tok = tok->next;
	}
	return (len);
}
