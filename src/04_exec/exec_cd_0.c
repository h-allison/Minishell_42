/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:08:11 by hallison          #+#    #+#             */
/*   Updated: 2025/04/09 15:08:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

char	*get_home_dir(char **envp)
{
	char	*home;
	char	*user;

	home = get_str_from_envp("HOME=", envp);
	if (home != NULL)
		return (ft_strdup(home));
	home = getenv("HOME");
	if (home != NULL)
		return (ft_strdup(home));
	user = getenv("USER");
	if (user != NULL)
		return (ft_strjoin("/home/", getenv("USER")));
	return (ft_strdup("/"));
}

/*
	chdir_to_home finds() $HOME in envp
	& tries to change to that directory.
	Returns 1 if HOME cannot be found or chdir() fails.
	Returns 0 on success.
*/
int	chdir_to_home(char ***envp)
{
	char	*home_path;
	int		exit_code;

	home_path = get_str_from_envp("HOME=", *envp);
	if (home_path == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	exit_code = change_directory(home_path);
	return (exit_code);
}

/*
	chdir_path_starts_from_home()
	is for "cd ~<path>"
	It builds a path from $HOME + argv[1]
	& tries to change to that directory.
	Returns exit code if HOME cannot be found or chdir() fails.
	Returns 0 on success.
*/

int	chdir_path_starts_from_home(t_shell *shell, char *cd_path, char ***envp)
{
	char	*home_path;
	char	*rebuilt_home_path;
	char	*full_path;
	int		exit_code;

	exit_code = 1;
	home_path = get_str_from_envp("HOME=", *envp);
	if (home_path != NULL)
		full_path = ft_strjoin(home_path, cd_path + 1);
	else
	{
		rebuilt_home_path = get_home_dir(*envp);
		full_path = ft_strjoin(rebuilt_home_path, cd_path + 1);
		free(rebuilt_home_path);
	}
	if (!full_path)
		return (ms_error_fail(shell, 1, "chdir_path_starts...", "malloc()"));
	exit_code = change_directory(full_path);
	free(full_path);
	return (exit_code);
}

bool	current_dir_found(void)
{
	char	*cwd_check;
	bool	found;

	cwd_check = getcwd(NULL, 0);
	if (cwd_check == NULL || cwd_check[0] == '\0')
		found = false;
	else
		found = true;
	free(cwd_check);
	return (found);
}

int	exec_cd(t_shell *shell, t_node *node, char ***envp)
{
	int		exit_code;

	if (node->args[1] && node->args[2])
		return (ms_error_cd(1, ""));
	if (strncmp(node->args[1], "..", 3) == 0 && current_dir_found() == false)
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (0);
	}
	exit_code = 0;
	if (node->args[1] == NULL)
		exit_code = chdir_to_home(envp);
	else if (node->args[1][0] == '~')
		exit_code = chdir_path_starts_from_home(shell, node->args[1], envp);
	else
		exit_code = change_directory(node->args[1]);
	if (exit_code == 0)
		update_pwd_and_old_pwd(shell, envp);
	return (exit_code);
}
