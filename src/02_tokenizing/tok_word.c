/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:05 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:34:24 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

/* void	tok_handle_word(t_shell *shell, int *i, t_token *tok)
{
	t_token_state	tok_state;
//	int				token_start;

	if (shell->input[*i] == '$' && shell->input[*i + 1] == '(')
		return ;
//	token_start = *i;
	if (!tok_check_cmdsub_ahead(shell, *i) \
			&& tok_handle_quoted_assign (shell, i, tok))
		return ;
	if (tok_split_assign(shell, i, tok))
		return ;
	tok_init_state(&tok_state, *i);
	tok_process_word_loop(shell, tok, &tok_state);
	*i = tok_state.pos;
	if (*i > tok_state.start)
		tok_add_segment(tok, &shell->input[tok_state.start], \
				&shell->input[tok_state.pos], tok_state.expand);
	tok->in_quote = tok_state.in_quote;
	tok->quote_char = tok_state.quote_char;
	tok->merge = tok_should_merge(shell->input, *i, tok->in_quote);
	tok_finish_word(shell, tok);
} */

void	tok_process_word_loop(t_shell *shell, t_token *tok, \
											t_token_state *state)
{
	while (shell->input[state->pos])
	{
		if (tok_handle_open_quote(shell, tok, state) \
			|| tok_handle_close_quote(shell, tok, state))
			continue ;
		if (!state->in_quote && shell->input[state->pos] == '$' \
				&& shell->input[state->pos + 1] == '(')
			break ;
		if (!state->in_quote && shell->input[state->pos] == '$')
			state->expand = true;
		if (!state->in_quote \
				&& tok_is_unclosed_boundary(shell->input[state->pos]))
			break ;
		state->pos++;
	}
}

void	tok_add_segment(t_token *token, char *start, char *end, bool expand)
{
	int			len;
	t_wordseg	*seg;
	t_wordseg	*tail;

	len = end - start;
	seg = gc_malloc(token->shell, sizeof(*seg), &token->shell->parser_mem);
	seg->text = gc_malloc(token->shell, len + 1, &token->shell->parser_mem);
	ft_memcpy(seg->text, start, len);
	seg->text[len] = '\0';
	seg->expand = expand;
	seg->next = NULL;
	if (!token->segs)
		token->segs = seg;
	else
	{
		tail = token->segs;
		while (tail->next)
			tail = tail->next;
		tail->next = seg;
	}
}

bool	tok_should_merge(char *input, int token_end, bool in_quote)
{
	char	next_char;

	next_char = input[token_end];
	if (next_char == '\0')
		return (false);
	if (next_char == ' ' || next_char == '\t' || next_char == '\n')
		return (false);
	if (tok_is_operator_start(next_char))
		return (false);
	if (in_quote)
		return (true);
	return (true);
}

void	tok_finish_word(t_shell *shell, t_token *token)
{
	t_wordseg	*seg;

	seg = token->segs;
	while (seg)
	{
		if (seg->expand && ft_strchr(seg->text, '$'))
		{
			token->expand = true;
			seg->text = tok_expand_vars(shell, seg->text);
		}
		seg = seg->next;
	}
	tok_flatten_segments(token);
	if (!token->quoted && token->expand
		&& token->value && token->value[0] == '\0')
		return ;
	token->type = T_WORD;
	token->prec = tok_get_precedence(token->type);
	tok_append_token(shell, token);
}

void	tok_handle_word(t_shell *shell, int *i, t_token *tok)
{
	t_token_state	tok_state;

	if (shell->input[*i] == '$' && shell->input[*i + 1] == '(')
		return ;
	if (!tok_check_cmdsub_ahead(shell, *i) \
			&& tok_handle_quoted_assign (shell, i, tok))
		return ;
	if (tok_split_assign(shell, i, tok))
		return ;
	tok_init_state(&tok_state, *i);
	tok_process_word_loop(shell, tok, &tok_state);
	*i = tok_state.pos;
	if (*i > tok_state.start)
		tok_add_segment(tok, &shell->input[tok_state.start], \
				&shell->input[tok_state.pos], tok_state.expand);
	tok->in_quote = tok_state.in_quote;
	tok->quote_char = tok_state.quote_char;
	tok->merge = tok_should_merge(shell->input, *i, tok->in_quote);
	tok_finish_word(shell, tok);
}
