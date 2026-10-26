/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:29:21 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:48:35 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	in_handle_error(t_shell *shell)
{
	if (shell->buffer && shell->buffer[0])
		add_history(shell->buffer);
	gc_free(shell->buffer, &shell->input_mem);
	shell->buffer = NULL;
	shell->input = NULL;
	return ;
}

t_input_status	in_handle_operator(char *buffer)
{
	int				i;
	t_input_status	stat;

	if (!buffer)
		return (IN_COMPLETE);
	stat = in_validate_operators(buffer);
	if (stat != IN_COMPLETE)
		return (stat);
	i = ft_strlen(buffer) - 1;
	while (i >= 0 && ft_isspace(buffer[i]))
		i--;
	if (i < 0)
		return (IN_COMPLETE);
	if (i > 0 && buffer[i] == '&' && buffer[i - 1] == '&')
		return (IN_INCOMPLETE);
	if (i > 0 && buffer[i] == '|')
		return (IN_INCOMPLETE);
	if (buffer[i] == '|')
		printf("minishell: syntax error near unexpected token `|'\n");
	return (IN_COMPLETE);
}

t_input_status	in_handle_separated_operators(const char *buffer)
{
	int		i;
	char	first_op;

	i = 0;
	while (buffer[i])
	{
		if (tok_is_operator_start(buffer[i]))
		{
			first_op = buffer[i];
			while (buffer[i] && tok_is_operator_start(buffer[i]))
				i++;
			while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
				i++;
			if (in_is_invalid_combination(first_op, buffer[i]))
			{
				in_print_operator_error(buffer, i);
				return (IN_ERROR);
			}
		}
		else
			i++;
	}
	return (IN_COMPLETE);
}
