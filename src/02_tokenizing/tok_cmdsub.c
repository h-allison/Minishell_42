/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cmdsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:21 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:36:21 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

void	tok_handle_cmdsub(t_shell *shell, int *i, t_token *tok)
{
	int		start;
	int		end;

	start = *i;
	end = tok_find_cmdsub_end(shell, i);
	tok_create_cmdsub_value(tok, shell, start, end);
	tok->type = T_CMDSUB;
	tok->prec = tok_get_precedence(tok->type);
	tok->merge = tok_should_merge(shell->input, \
		end, tok->in_quote);
	tok_append_token(shell, tok);
}

int	tok_find_cmdsub_end(t_shell *shell, int *i)
{
	int	depth;

	*i += 2;
	depth = 1;
	while (shell->input[*i] && depth)
	{
		if (shell->input[*i] == '(')
			depth++;
		else if (shell->input[*i] == ')')
			depth--;
		(*i)++;
	}
	return (*i);
}

void	tok_create_cmdsub_value(t_token *tok, t_shell *shell, \
	int start, int end)
{
	int	len;

	len = end - start;
	tok->value = gc_malloc(shell, len + 1, &shell->parser_mem);
	ft_memcpy(tok->value, shell->input + start, len);
	tok->value[len] = '\0';
}

bool	tok_check_cmdsub_ahead(t_shell *shell, int start)
{
	int	check;

	check = start;
	while (shell->input[check])
	{
		if (shell->input[check] == '$' && shell->input[check + 1] == '(')
			return (true);
		if (tok_is_unclosed_boundary(shell->input[check]))
			break ;
		check++;
	}
	return (false);
}

int	tok_validate_var_name(const char *input)
{
	int	pos;

	if (!input)
		return (0);
	if (!ft_isalpha(input[0]) && input[0] != '_')
		return (0);
	pos = 1;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	if (input[pos] != '=')
		return (0);
	return (pos + 1);
}
