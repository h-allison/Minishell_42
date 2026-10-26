/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:42:37 by hallison          #+#    #+#             */
/*   Updated: 2025/07/04 16:06:56 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_core.h"

/*
	find_env_index() searches for a variable (expected format is "VARIABLE=")
	by comparing up to match_len chars (match_len = strlen(var)).
	Returns EITHER
	- the index of the line, if it exists
	- -42, if not found
*/

int	find_env_index(char *var, int match_len, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], var, match_len) != 0)
		i++;
	if (envp[i] == NULL)
		return (-42);
	else
		return (i);
}

/* A second version of find_env_index that does not require "=" as part
of the var argument. Convenient for use with unset. "*/

// TODO: This function is better than previous version and could replace
// it everywhere, but other functions would need to be updated
int	find_env_index_2(char *var, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		if (envp[i][j] == var[j])
		{
			while ((envp[i][j] == var[j]) && (envp[i][j] != '\0') \
												&& (var[j] != '\0'))
				j++;
			if (envp[i][j] == '=' && var[j] == '\0')
				return (i);
		}
		i++;
	}
	return (-42);
}

/*
get_str_from_envp() returns a pointer to a particular substring in envp;
The argument var_name must include "=" sign, i.e. "VARIABLE=""
*/
char	*get_str_from_envp(char *var_name, char **envp)
{
	int	i;
	int	match_len;

	match_len = ft_strlen(var_name);
	i = find_env_index(var_name, match_len, envp);
	if (i < 0)
		return (NULL);
	return (envp[i] + match_len);
}

char	*gc_strdup(t_shell *shell, const char *src, t_gc_mem *mem)
{
	char	*dup;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dup = gc_malloc(shell, len + 1, mem);
	ft_strlcpy(dup, src, len + 1);
	return (dup);
}
