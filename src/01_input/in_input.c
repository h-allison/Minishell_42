/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:52:27 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/27 19:32:15 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	in_input_loop(t_shell *shell)
{
	shell->buffer = NULL;
	while (1)
	{
		in_get_input(shell);
		in_check_status(shell);
		if (shell->in_status == IN_ERROR || shell->in_status == IN_QUOTE_ERR)
		{
			in_handle_error(shell);
			if (shell->in_status == IN_QUOTE_ERR)
				printf("minishell: error: unclosed quotes detected :(\n");
			continue ;
		}
		if (shell->in_status == IN_COMPLETE)
			break ;
	}
	if (shell->buffer && shell->buffer[0])
		add_history(shell->buffer);
	shell->input = shell->buffer;
}

void	in_get_input(t_shell *shell)
{
	char	*line;

	if (!shell->buffer)
		prompt_update(shell);
	else
		shell->prompt = prompt_alt(shell);
	line = readline(shell->prompt);
	if (!line)
		ms_clean_exit(shell, 0, true);
	in_append_input(shell, &shell->buffer, line);
	free(line);
	return ;
}

void	in_append_input(t_shell *shell, char **buffer, char *line)
{
	char	*old_in;
	char	*new_in;
	size_t	len_old;
	size_t	len_line;

	old_in = *buffer;
	if (!old_in)
	{
		*buffer = gc_strdup(shell, line, &shell->input_mem);
		return ;
	}
	len_old = ft_strlen(old_in);
	len_line = ft_strlen(line);
	new_in = gc_malloc(shell, len_old + len_line + 2, &shell->input_mem);
	ft_strcpy(new_in, old_in);
	new_in[len_old] = '\n';
	ft_strcpy(new_in + len_old + 1, line);
	*buffer = new_in;
}

void	in_check_status(t_shell *shell)
{
	t_input_status	stat;
	int				skip;
	char			*rest;

	rest = shell->buffer;
	skip = tok_skip_quoted_segment(rest);
	if (skip > 0)
	{
		if (rest[skip] == '\0')
		{
			shell->in_status = IN_COMPLETE;
			return ;
		}
		rest += skip;
	}
	stat = in_check_parens(rest);
	if (stat == IN_COMPLETE)
		stat = in_check_quotes(shell->buffer);
	if (stat == IN_COMPLETE)
		stat = in_handle_operator(shell->buffer);
	shell->in_status = stat;
}
