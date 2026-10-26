/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:26:48 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:37:55 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

t_input_status	in_check_quotes(char *buf)
{
	bool	in_quotes;
	char	quote;
	int		i;

	in_quotes = false;
	quote = '\0';
	i = 0;
	while (buf[i])
	{
		in_process_quote_char(buf[i], &in_quotes, &quote);
		i++;
	}
	if (in_quotes)
		return (IN_QUOTE_ERR);
	return (IN_COMPLETE);
}

void	in_process_quote_char(char c, bool *in_quotes, char *quote)
{
	if (!*in_quotes && (c == '"' || c == '\''))
	{
		*in_quotes = true;
		*quote = c;
	}
	else if (*in_quotes && c == *quote)
	{
		*in_quotes = false;
		*quote = '\0';
	}
}

char	*in_skip_quote(char *buf_ptr)
{
	char	quote;

	quote = *buf_ptr;
	buf_ptr++;
	while (*buf_ptr && *buf_ptr != quote)
		buf_ptr++;
	return (buf_ptr);
}

t_input_status	in_check_single_amp(const char *buffer, int start, int op_rep)
{
	int	i;

	if (op_rep == 1 && buffer[start] == '&')
	{
		i = start + 1;
		while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
			i++;
		if (buffer[i] && tok_is_operator_start(buffer[i]))
			return (IN_COMPLETE);
		printf("minishell does not support backgrounding: ");
		printf("syntax error near unexpected token `&'\n");
		return (IN_ERROR);
	}
	return (IN_COMPLETE);
}
