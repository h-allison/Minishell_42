/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:48:46 by hallison          #+#    #+#             */
/*   Updated: 2025/03/26 15:50:09 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Functions related to PATH. Includes:
	- get_path() for execution of cd (may also have other uses?)
	- TODO: function to set PATH using export
*/

#include "ms_exec.h"

bool	is_a_path(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			return (true);
		else
			i++;
	}
	return (false);
}

void	free_directories(char **directories)
{
	int	i;

	i = 0;
	while (directories[i] != NULL)
	{
		free(directories[i]);
		i++;
	}
	free (directories);
}

char	*dup_path(t_shell *shell, char *path)
{
	char	*return_path;

	return_path = ft_strdup(path);
	if (!return_path)
	{
		(ms_error_fail(shell, 1, "get_path()", "malloc()"));
		return (NULL);
	}
	return (return_path);
}

/*
	get_path() builds a path to a given command

	1) gets list of directories using getenv("PATH") and ft_split()
	2) iterates over each directory...
		- adds "/<command>" to each directory path
		- checks if this file exists & is executable
		- if yes, returns strdup of this path 
*/

char	*get_path(t_shell *shell, char *command, char **envp)
{
	char	**directories;
	char	path[PATH_MAX];
	int		i;

	directories = ft_split(get_str_from_envp("PATH=", envp), ':');
	if (!directories)
		return (NULL);
	i = 0;
	while (directories[i])
	{
		ft_strlcpy(path, directories[i], PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, command, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			free_directories(directories);
			return (dup_path(shell, path));
		}
		i++;
	}
	free_directories(directories);
	return (NULL);
}
