/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:53:38 by hallison          #+#    #+#             */
/*   Updated: 2025/06/24 15:53:39 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	change_directory(char *path)
{
	int	exit_code;

	exit_code = 0;
	if (access(path, F_OK) != 0)
		exit_code = ms_error_cd(2, path);
	else if (is_directory(path) == 0)
		exit_code = ms_error_cd(3, path);
	else if (access(path, X_OK) != 0)
		exit_code = ms_error_cd(4, path);
	else if (chdir(path) != 0)
		exit_code = ms_error_cd(0, path);
	return (exit_code);
}

int	update_pwd_and_old_pwd(t_shell *shell, char ***envp)
{
	char	*pwd;

	pwd = malloc((PATH_MAX + 1 + 4) * sizeof(char));
	if (!pwd)
		return (ms_error_fail(shell, 1, "update_pwd_and_old...", "malloc()"));
	ft_strcpy(pwd, "PWD=");
	if (getcwd(pwd + 4, PATH_MAX + 1) == NULL)
	{
		free(pwd);
		return (-1);
	}
	getcwd(shell->protected_cwd, PATH_MAX + 1);
	auto_export(shell, pwd, envp);
	free(pwd);
	return (0);
}
