/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:25:21 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/30 15:16:13 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

t_input_status	in_check_parens(char *buffer)
{
	int				depth;
	char			*buf_pt;

	depth = 0;
	buf_pt = buffer;
	while (*buf_pt)
	{
		if (*buf_pt == '"' || *buf_pt == '\'')
		{
			buf_pt = in_skip_quote(buf_pt);
			if (*buf_pt == '\0')
				break ;
		}
		else if (*buf_pt == '(' || (*buf_pt == '$' && *(buf_pt + 1) == '('))
			in_handle_paren_char(&buf_pt, &depth);
		else if (*buf_pt == ')')
		{
			if (in_handle_closing_paren(&depth) == IN_ERROR)
				return (IN_ERROR);
		}
		buf_pt++;
	}
	if (depth > 0)
		return (IN_INCOMPLETE);
	return (IN_COMPLETE);
}

void	in_handle_paren_char(char **buf_pt, int *depth)
{
	if (**buf_pt == '$' && *(*buf_pt + 1) == '(')
	{
		(*depth)++;
		(*buf_pt)++;
	}
	else if (**buf_pt == '(')
		(*depth)++;
}

t_input_status	in_handle_closing_paren(int *depth)
{
	if (*depth == 0)
	{
		printf("minishell: syntax error near unexpected token `)'\n");
		return (IN_ERROR);
	}
	(*depth)--;
	return (IN_COMPLETE);
}

int	in_count_redirect_operators(const char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '<' || buffer[i] == '>')
		{
			count++;
			if (buffer[i + 1] == buffer[i])
				i++;
		}
		i++;
	}
	return (count);
}

t_input_status	in_check_trailing_operators(const char *buffer)
{
	if (in_count_redirect_operators(buffer) == 1 && \
						in_ends_with_redirect(buffer))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (IN_ERROR);
	}
	return (IN_COMPLETE);
}
