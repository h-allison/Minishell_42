/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:09:59 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/30 15:56:50 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

bool	in_is_invalid_combination(char first_op, char next_char)
{
	if (first_op == '|' && (next_char == '|' || next_char == '&'))
		return (true);
	if (first_op == '&' && (next_char == '&' || next_char == '|'))
		return (true);
	if ((first_op == '<' || first_op == '>') \
				&& (next_char == '<' || next_char == '>'))
		return (true);
	if ((first_op == '<' || first_op == '>') && next_char == '|')
		return (true);
	return (false);
}

void	in_print_operator_error(const char *buffer, int pos)
{
	if (buffer[pos] == '>' && buffer[pos + 1] == '>')
		printf("minishell: syntax error near unexpected token `>>'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", \
			buffer[pos]);
}

bool	in_ends_with_redirect(const char *buffer)
{
	int	len;
	int	i;

	len = strlen(buffer);
	if (len == 0)
		return (false);
	i = len - 1;
	while (i >= 0 && (buffer[i] == ' ' || buffer[i] == '\t'))
		i--;
	return (i >= 0 && (buffer[i] == '<' || buffer[i] == '>'));
}
