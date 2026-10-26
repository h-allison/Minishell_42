/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:05:50 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:40:03 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

/* bool	tok_handle_quoted_assign(t_shell *shell, int *i, t_token *tok)
{
	int		len;

	len = tok_skip_quoted_segment(&shell->input[*i]);
	if (len == 0)
		return (false);
	tok_add_segment(tok, &shell->input[*i], &shell->input[*i + len], false);
	tok_finish_word(shell, tok);
	*i += len;
	return (true);
} */

int	tok_skip_quoted_segment(const char *input)
{
	int	pos;
	int	new_pos;

	pos = tok_validate_var_name(input);
	if (!pos)
		return (0);
	while (input[pos])
	{
		if (input[pos] == '"' || input[pos] == '\'')
		{
			new_pos = tok_skip_quote_content(input, pos + 1, input[pos]);
			if (!new_pos)
				return (0);
			pos = new_pos;
		}
		else if (tok_is_token_boundary(input[pos]))
			break ;
		else
			pos++;
	}
	return (pos);
}

int	tok_skip_quote_content(const char *input, int start, char quote)
{
	int		pos;
	bool	closing_quote;

	pos = start;
	closing_quote = false;
	while (input[pos])
	{
		if (input[pos] == quote)
		{
			pos++;
			closing_quote = true;
			break ;
		}
		else
			pos++;
	}
	if (!closing_quote)
		return (pos);
	return (0);
}

bool	tok_handle_open_quote(t_shell *shell, t_token *tok, \
							t_token_state *tok_state)
{
	char	c;

	c = shell->input[tok_state->pos];
	if (tok->in_quote || (c != '\'' && c != '"'))
		return (false);
	if (tok_state->pos > tok_state->start)
		tok_add_segment(tok, &shell->input[tok_state->start], \
					&shell->input[tok_state->pos], tok_state->expand);
	if (!tok->quoted)
	{
		if (c == '\'')
			tok->quoted = 1;
		else
			tok->quoted = 2;
	}
	tok->in_quote = true;
	tok_state->in_quote = true;
	tok->quote_char = c;
	tok_state->quote_char = c;
	tok_state->expand = (c == '"');
	tok_state->start = tok_state->pos + 1;
	tok_state->pos++;
	return (true);
}

// For double quotes, check if this quote is escaped
// Note: Single quotes don't support escaping in bash
bool	tok_handle_close_quote(t_shell *shell, t_token *tok, \
										t_token_state *tok_state)
{
	char	c;

	c = shell->input[tok_state->pos];
	if (!tok->in_quote || c != tok->quote_char)
		return (false);
	if (tok_state->pos > tok_state->start)
		tok_add_segment(tok, &shell->input[tok_state->start], \
					&shell->input[tok_state->pos], tok_state->expand);
	tok->in_quote = false;
	tok_state->in_quote = false;
	tok_state->expand = true;
	tok_state->start = tok_state->pos + 1;
	tok_state->pos++;
	return (true);
}

bool	tok_handle_quoted_assign(t_shell *shell, int *i, t_token *tok)
{
	int		len;
	int		j;
	bool	has_quotes;

	len = tok_skip_quoted_segment(&shell->input[*i]);
	if (len == 0)
		return (false);
	has_quotes = false;
	j = *i;
	while (j < *i + len)
	{
		if (shell->input[j] == '"' || shell->input[j] == '\'')
		{
			has_quotes = true;
			break ;
		}
		j++;
	}
	if (!has_quotes)
		return (false);
	tok_add_segment(tok, &shell->input[*i], &shell->input[*i + len], false);
	tok_finish_word(shell, tok);
	*i += len;
	return (true);
}
