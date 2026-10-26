/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:32 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 14:53:56 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tokenizing.h"

char	*tok_expand_vars(t_shell *shell, char *line)
{
	char	*result;
	int		i;

	result = gc_malloc(shell, 1, &shell->parser_mem);
	result[0] = '\0';
	i = 0;
	while (line[i])
		result = tok_expand_token(shell, line, result, &i);
	return (result);
}

char	*tok_expand_token(t_shell *shell, char *line, char *result, int *i)
{
	char	*var;
	char	*var_with_equals;
	int		start;

	if (line[*i] == '$' && line[*i + 1] == '?')
		result = tok_append_status(shell, result, i);
	else if (line[*i] == '$' && (ft_isalpha(line[*i + 1]) \
				|| line[*i + 1] == '_'))
	{
		start = ++(*i);
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*i)++;
		var = ft_substr(line, start, *i - start);
		var_with_equals = ft_strjoin(var, "=");
		result = tok_append_var(shell, result, \
					get_str_from_envp(var_with_equals, shell->envp));
		free(var);
		free(var_with_equals);
	}
	else
	{
		result = tok_append_char(shell, result, line[*i]);
		(*i)++;
	}
	return (result);
}

char	*tok_append_status(t_shell *shell, char *result, int *i)
{
	char	*code;
	char	*tmp;

	code = ft_itoa(shell->last_exit_code);
	tmp = tok_append_var(shell, result, code);
	free (code);
	(*i) += 2;
	return (tmp);
}

char	*tok_append_var(t_shell *shell, char *base, char *add)
{
	char	*new;
	size_t	len;

	if (!add)
		return (base);
	len = ft_strlen(base) + ft_strlen(add) + 1;
	new = gc_malloc(shell, len, &shell->parser_mem);
	if (!new)
		return (NULL);
	ft_strlcpy(new, base, len);
	ft_strlcat(new, add, len);
	gc_free(base, &shell->parser_mem);
	return (new);
}

char	*tok_append_char(t_shell *shell, char *base, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (tok_append_var(shell, base, tmp));
}
