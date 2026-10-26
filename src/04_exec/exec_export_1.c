/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:54:05 by hallison          #+#    #+#             */
/*   Updated: 2025/05/29 14:54:07 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	auto_export(t_shell *shell, char *var, char ***envp)
{
	int	i;
	int	rc;

	rc = 0;
	i = find_env_index(var, get_var_len(var), *envp);
	if (i < 0)
		rc = realloc_and_add_var_to_envp(shell, var, envp);
	else
		rc = (update_var(var, envp));
	return (rc);
}

int	update_var(char *var, char ***envp)
{
	int	i;

	i = find_env_index(var, get_var_len(var), *envp);
	if (i < 0)
	{
		ft_putstr_fd("VAR to be updated not found in envp\n", 2);
		return (1);
	}
	free((*envp)[i]);
	(*envp)[i] = ft_strdup(var);
	if (!(*envp)[i])
		return (-1);
	return (0);
}

int	add_var_to_export(t_shell *shell, char ***export_list, char *var, int i)
{
	char	**temp_export_list;
	char	**old;

	while ((*export_list)[i] != NULL)
		i++;
	temp_export_list = malloc((i + 2) * sizeof(char *));
	if (!temp_export_list)
		return (ms_error_fail(shell, 1, "add_var_to_export()", "malloc()"));
	i = 0;
	while ((*export_list)[i] != NULL)
	{
		temp_export_list[i] = ft_strdup((*export_list)[i]);
		if (!temp_export_list[i])
			return (ms_error_fail(shell, 1, "add_var_to_export()", "malloc()"));
		i++;
	}
	temp_export_list[i] = ft_strdup(var);
	if (!temp_export_list[i])
		return (ms_error_fail(shell, 1, "add_var_to_export()", "ft_strdup()"));
	temp_export_list[i + 1] = NULL;
	old = *export_list;
	*export_list = temp_export_list;
	free_arguments(old);
	return (0);
}

int	export_var_no_assign(t_shell *shl, char *var, char ***lst, char **envp)
{
	char	*var_equals;

	var_equals = ft_strjoin(var, "=");
	if (find_env_index(var_equals, ft_strlen(var) + 1, envp) == -42)
	{
		free (var_equals);
		return (add_var_to_export(shl, lst, var, 0));
	}
	else
	{
		free (var_equals);
		return (0);
	}
}
