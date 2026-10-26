/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:32:52 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 19:55:28 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

void	tok_handle_redirect(t_shell *shell, int *i, t_token *token)
{
	if (shell->input[*i] == '>' && shell->input[*i + 1] == '>')
		tok_add_append(shell, i, token);
	else if (shell->input[*i] == '<' && shell->input[*i + 1] == '<')
		tok_add_heredoc(shell, i, token);
	else if (shell->input[*i] == '<')
		tok_add_input(shell, i, token);
	else if (shell->input[*i] == '>')
		tok_add_output(shell, i, token);
	else
		return ;
	token->prec = tok_get_precedence(token->type);
	tok_append_token(shell, token);
}

void	tok_add_append(t_shell *shell, int *i, t_token *token)
{
	token->type = T_APPEND;
	token->value = gc_malloc(shell, 3, &shell->parser_mem);
	ft_strlcpy(token->value, ">>", 3);
	*i += 2;
	(void) shell;
}

void	tok_add_heredoc(t_shell *shell, int *i, t_token *token)
{
	token->type = T_HEREDOC;
	token->value = gc_malloc(shell, 3, &shell->parser_mem);
	ft_strlcpy(token->value, "<<", 3);
	*i += 2;
	(void) shell;
}

void	tok_add_input(t_shell *shell, int *i, t_token *token)
{
	token->type = T_INPUT;
	token->value = gc_malloc(shell, 2, &shell->parser_mem);
	ft_strlcpy(token->value, "<", 2);
	(*i)++;
	(void) shell;
}

void	tok_add_output(t_shell *shell, int *i, t_token *token)
{
	token->type = T_OUTPUT;
	token->value = gc_malloc(shell, 2, &shell->parser_mem);
	ft_strlcpy(token->value, ">", 2);
	(*i)++;
	(void) shell;
}
