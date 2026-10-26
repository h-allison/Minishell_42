/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:35:21 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/30 13:32:57 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

void	tok_handle_operator(t_shell *shell, int *i, t_token *token)
{
	if (shell->input[*i] == '&' && shell->input[*i + 1] == '&')
		token->type = T_AND;
	else if (shell->input[*i] == '|' && shell->input[*i + 1] == '|')
		token->type = T_OR;
	else if (shell->input[*i] == '|')
	{
		tok_handle_pipe(shell, i, token);
		return ;
	}
	else
		return ;
	token->value = gc_malloc(shell, 3, &shell->parser_mem);
	token->value[0] = shell->input[*i];
	token->value[1] = shell->input[*i + 1];
	token->value[2] = '\0';
	token->prec = tok_get_precedence(token->type);
	tok_append_token(shell, token);
	*i += 2;
}

void	tok_handle_pipe(t_shell *shell, int *i, t_token *token)
{
	token->type = T_PIPE;
	token->value = gc_malloc(shell, 2, &shell->parser_mem);
	token->value[0] = '|';
	token->value[1] = '\0';
	token->prec = tok_get_precedence(token->type);
	tok_append_token(shell, token);
	(*i)++;
}

void	tok_handle_paren(t_shell *shell, int *i, t_token *token)
{
	if (shell->input[*i] == '(')
		token->type = T_OPEN_PAREN;
	else
		token->type = T_CLOSE_PAREN;
	token->value = gc_malloc(shell, 2, &shell->parser_mem);
	token->value[0] = shell->input[*i];
	token->value[1] = '\0';
	token->prec = tok_get_precedence(token->type);
	tok_append_token(shell, token);
	(*i)++;
}

bool	tok_is_operator_start(char c)
{
	return (c == '|' || c == '&' || c == '>' || c == '<');
}
