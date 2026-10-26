/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:43:44 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:53:44 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

int	tok_find_token_end(t_shell *shell, int start)
{
	int	j;

	j = start;
	while (shell->input[j] && !ft_isspace(shell->input[j]) \
					&& !tok_is_token_boundary(shell->input[j]))
		j++;
	return (j);
}

char	*tok_find_assignment_operator(t_shell *shell, int start, int end)
{
	char	*equal_pos;

	equal_pos = ft_strchr(&shell->input[start], '=');
	if (!equal_pos || equal_pos >= &shell->input[end])
		return (NULL);
	return (equal_pos);
}

void	tok_add_assignment_segments(t_shell *shell, t_token *tok, \
													int start, int len)
{
	char	*equal_pos;
	int		name_len;
	bool	should_expand;

	equal_pos = ft_strchr(&shell->input[start], '=');
	name_len = equal_pos - &shell->input[start] + 1;
	tok_add_segment(tok, &shell->input[start], \
					&shell->input[start + name_len], false);
	if (name_len < len)
	{
		should_expand = (ft_strchr(&shell->input[start + name_len], '$') \
																!= NULL);
		tok_add_segment(tok, &shell->input[start + name_len], \
						&shell->input[start + len], should_expand);
	}
}

bool	tok_split_assign(t_shell *shell, int *i, t_token *tok)
{
	int		len;
	int		token_end;
	char	*equal_pos;

	if (!(ft_isalpha(shell->input[*i]) || shell->input[*i] == '_'))
		return (false);
	token_end = tok_find_token_end(shell, *i);
	equal_pos = tok_find_assignment_operator(shell, *i, token_end);
	if (!equal_pos)
		return (false);
	len = tok_skip_quoted_segment(&shell->input[*i]);
	if (len == 0)
		return (false);
	tok_add_assignment_segments(shell, tok, *i, len);
	tok_finish_word(shell, tok);
	*i += len;
	return (true);
}
