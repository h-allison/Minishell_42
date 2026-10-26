/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:02:46 by cbotel            #+#    #+#             */
/*   Updated: 2025/06/25 19:19:14 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

char	*prompt_find_first_dir(t_shell *shell, const char *str)
{
	int		i;
	char	*first;

	i = 0;
	if (!str || str[i] != '/')
		return (NULL);
	if (str[i])
		i++;
	while (str[i] && str[i] != '/')
		i++;
	first = gc_malloc(shell, i + 1, &shell->input_mem);
	ft_strlcpy(first, str, i + 1);
	return (first);
}

char	*prompt_find_last_dir(char *str)
{
	int		i;
	char	*ptr_to_last;

	i = 0;
	ptr_to_last = str;
	while (str[i])
	{
		if (str[i] == '/')
			ptr_to_last = &str[i];
		i++;
	}
	return (ptr_to_last);
}

// getenv returns static string that must not be freed
bool	prompt_path_has_home(char *str)
{
	char	*home;
	size_t	len_home;

	home = getenv("HOME");
	if (!home)
		return (false);
	len_home = ft_strlen(home);
	if (!ft_strncmp(str, home, len_home) && \
		(str[len_home] == '/' || str[len_home] == '\0'))
		return (true);
	else
		return (false);
}

char	*prompt_cwd(t_shell *shell)
{
	char	*cwd;
	char	*short_cwd;
	char	*final;
	int		level;
	size_t	len;

	level = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("?");
	short_cwd = prompt_shorten_cwd(shell, cwd, &level);
	len = ft_strlen(short_cwd);
	final = gc_malloc(shell, len + 2, &shell->input_mem);
	ft_strlcpy(final, short_cwd, len + 2);
	final[len] = ' ';
	final[len + 1] = '\0';
	free(cwd);
	return (final);
}

char	*prompt_alt(t_shell *shell)
{
	char	*prompt;

	prompt = gc_malloc(shell, 3, &shell->input_mem);
	prompt[0] = '>';
	prompt[1] = ' ';
	prompt[2] = '\0';
	return (prompt);
}
