/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_segments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:19:19 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:40:29 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

size_t	tok_calc_total_len(t_wordseg *seg)
{
	size_t	total;

	total = 0;
	while (seg)
	{
		total += ft_strlen(seg->text);
		seg = seg->next;
	}
	return (total);
}

void	tok_flatten_segments(t_token *token)
{
	t_wordseg	*seg;
	size_t		total;
	size_t		len;
	char		*dest;

	total = tok_calc_total_len(token->segs);
	token->value = gc_malloc(token->shell, total + 1, \
								&token->shell->parser_mem);
	dest = token->value;
	seg = token->segs;
	while (seg)
	{
		len = ft_strlen(seg->text);
		memcpy(dest, seg->text, len);
		dest += len;
		seg = seg->next;
	}
	*dest = '\0';
}

void	tok_append_token(t_shell *shell, t_token *token)
{
	t_token	*curr;

	token->next = NULL;
	if (!shell->tokens)
		shell->tokens = token;
	else
	{
		curr = shell->tokens;
		while (curr->next)
			curr = curr->next;
		curr->next = token;
	}
}

// 1) Normal token boundary: stops at space, op, or ANY quote
bool	tok_is_token_boundary(char c)
{
	return (c == '\0' || c == ' ' || c == '\t'
		|| c == '\n' || c == '|' || c == '<'
		|| c == '>' || c == '(' || c == ')'
		|| c == '\'' || c == '"');
}

// 2) Fallback boundary: ignores quotes, only stops at real separators
bool	tok_is_unclosed_boundary(char c)
{
	return (c == '\0' || c == ' ' || c == '\t'
		|| c == '\n' || c == '|' || c == '<'
		|| c == '>' || c == '(' || c == ')'
		|| c == '&');
}
