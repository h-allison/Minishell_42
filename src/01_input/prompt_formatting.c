/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_formatting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:50:23 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 20:37:47 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

char	*prompt_colorize(t_shell *shell, const char *color, const char *str)
{
	char	*res;
	size_t	len;

	len = ft_strlen(RL_START_IGNORE) + ft_strlen(color) +\
		ft_strlen(RL_END_IGNORE) + ft_strlen(str) +\
		ft_strlen(RL_START_IGNORE) + ft_strlen(RESET_COL) +\
		ft_strlen(RL_END_IGNORE) + 1;
	res = gc_malloc(shell, len + 1, &shell->input_mem);
	ft_strlcpy(res, RL_START_IGNORE, len);
	ft_strlcat(res, color, len);
	ft_strlcat(res, RL_END_IGNORE, len);
	ft_strlcat(res, str, len);
	ft_strlcat(res, RL_START_IGNORE, len);
	ft_strlcat(res, RESET_COL, len);
	ft_strlcat(res, RL_END_IGNORE, len);
	return (res);
}

char	*prompt_shorten_cwd(t_shell *shell, char *str, int	*level)
{
	int		i;
	char	*first;
	char	*last;
	char	*res_path;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			(*level)++;
		i++;
	}
	if (*level <= 2)
	{
		res_path = gc_malloc(shell, i + 1, &shell->input_mem);
		ft_strlcpy(res_path, str, i + 1);
		return (res_path);
	}
	first = prompt_find_first_dir(shell, str);
	last = prompt_find_last_dir(str);
	if (prompt_path_has_home(str))
		return (prompt_shorten_home(shell, last, *level));
	else
		return (prompt_shorten_path(shell, first, last));
}

char	*prompt_shorten_home(t_shell *shell, char *last, int level)
{
	char	*res_path;
	size_t	len;

	if (level == 3)
		len = 1 + ft_strlen(last) + 1;
	else
		len = 5 + ft_strlen(last) + 1;
	res_path = gc_malloc(shell, len + 1, &shell->input_mem);
	if (level == 3)
	{
		ft_strlcpy(res_path, "~", len + 1);
		ft_strlcat(res_path, last, len + 1);
	}
	else
	{
		ft_strlcpy(res_path, "~/...", len + 1);
		ft_strlcat(res_path, last, len + 1);
	}
	return (res_path);
}

char	*prompt_shorten_path(t_shell *shell, char *first, char *last)
{
	char	*res_path;
	size_t	len;

	len = ft_strlen(first) + 4 + ft_strlen(last) + 1;
	res_path = gc_malloc(shell, len + 1, &shell->input_mem);
	ft_strlcpy(res_path, first, len + 1);
	ft_strlcat(res_path, "/...", len + 1);
	ft_strlcat(res_path, last, len + 1);
	return (res_path);
}

char	*prompt_name(t_shell *shell)
{
	char	*name;
	size_t	len;

	len = ft_strlen("<minishell> ") + 1;
	name = gc_malloc(shell, len, &shell->input_mem);
	ft_strcpy(name, "<minishell> ");
	return (name);
}
