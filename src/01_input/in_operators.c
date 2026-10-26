/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_operators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:20:45 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/30 17:16:55 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

t_input_status	in_run_all_checks(const char *buffer)
{
	t_input_status	status;

	status = in_check_trailing_operators(buffer);
	if (status == IN_ERROR)
		return (IN_ERROR);
	status = in_handle_separated_operators(buffer);
	if (status == IN_ERROR)
		return (IN_ERROR);
	return (IN_COMPLETE);
}

t_input_status	in_validate_operators(const char *buffer)
{
	int				i;
	int				op_start;
	t_input_status	status;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '&' || buffer[i] == '|' || \
			buffer[i] == '<' || buffer[i] == '>')
		{
			op_start = i;
			while (buffer[i] == '&' || buffer[i] == '|' \
					|| buffer[i] == '<' || buffer[i] == '>')
				i++;
			status = in_check_op_sequence(buffer, op_start, i);
			if (status == IN_ERROR)
				return (IN_ERROR);
		}
		else
			i++;
	}
	status = in_run_all_checks(buffer);
	if (status == IN_ERROR)
		return (IN_ERROR);
	return (IN_COMPLETE);
}

t_input_status	in_check_op_sequence(const char *buffer, int start, int end)
{
	int				op_rep;
	t_input_status	status;

	op_rep = end - start;
	status = in_check_single_amp(buffer, start, op_rep);
	if (status == IN_ERROR)
		return (IN_ERROR);
	status = in_check_mixed_ops(buffer, start, end);
	if (status == IN_ERROR)
		return (IN_ERROR);
	return (in_check_op_rep(buffer, start, end, op_rep));
}

t_input_status	in_check_mixed_ops(const char *buffer, int start, int end)
{
	int	i;

	i = start;
	while (i < end - 1)
	{
		if (buffer[i] != buffer[i + 1])
		{
			printf("minishell: syntax error near unexpected token `%c%c'\n", \
				buffer[end - 2], buffer[end - 1]);
			return (IN_ERROR);
		}
		i++;
	}
	return (IN_COMPLETE);
}

t_input_status	in_check_op_rep(const char *buffer, \
								int start, int end, int op_rep)
{
	if (start == 0 && op_rep == 2)
	{
		printf("minishell: syntax error near unexpected token `%c%c'\n",
			buffer[end - 2], buffer[end - 1]);
		return (IN_ERROR);
	}
	if (op_rep == 3)
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			buffer[end - 1]);
		return (IN_ERROR);
	}
	if (op_rep >= 4)
	{
		printf("minishell: syntax error near unexpected token `%c%c'\n",
			buffer[end - 2], buffer[end - 1]);
		return (IN_ERROR);
	}
	return (IN_COMPLETE);
}
