/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:10:28 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:49:31 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

void	tok_tokenize(t_shell *shell)
{
	int				i;
	t_token			*token;

	i = 0;
	while (shell->input[i])
	{
		if (ft_isspace(shell->input[i]))
		{
			i++;
			continue ;
		}
		token = tok_init_token(shell);
		tok_handle_token_type(shell, &i, token);
	}
}

t_token	*tok_init_token(t_shell *shell)
{
	t_token	*token;

	token = gc_malloc(shell, sizeof(t_token), &shell->parser_mem);
	ft_bzero(token, sizeof(*token));
	token->shell = shell;
	token->value = gc_malloc(shell, 1, &shell->parser_mem);
	token->value[0] = '\0';
	token->type = T_ERROR;
	token->prec = PREC_HIGHEST;
	return (token);
}

void	tok_handle_token_type(t_shell *shell, int *i, \
	t_token *token)
{
	if (shell->input[*i] == '$' && shell->input[*i + 1] == '(')
		tok_handle_cmdsub(shell, i, token);
	else if (shell->input[*i] == '<' || shell->input[*i] == '>')
		tok_handle_redirect(shell, i, token);
	else if (shell->input[*i] == '&' || shell->input[*i] == '|')
		tok_handle_operator(shell, i, token);
	else if (shell->input[*i] == '(' || shell->input[*i] == ')')
		tok_handle_paren(shell, i, token);
	else
		tok_handle_word(shell, i, token);
}

t_precedence	tok_get_precedence(t_token_type type)
{
	if (type == T_PIPE)
		return (PREC_PIPE);
	if (type == T_OUTPUT || type == T_INPUT || \
		type == T_APPEND || type == T_HEREDOC)
		return (PREC_REDIRECT);
	if (type == T_OPEN_PAREN || type == T_CLOSE_PAREN || type == T_CMDSUB)
		return (PREC_SUBSHELL);
	if (type == T_AND || type == T_OR)
		return (PREC_LOGIC);
	return (PREC_HIGHEST);
}

void	tok_init_state(t_token_state *state, int pos)
{
	state->pos = pos;
	state->start = pos;
	state->in_quote = false;
	state->quote_char = 0;
	state->expand = false;
}
