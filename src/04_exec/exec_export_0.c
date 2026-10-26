/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:30 by hallison          #+#    #+#             */
/*   Updated: 2025/03/25 16:52:35 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

/*
	realloc_and_add_var_to_envp() reallocs and adds 1 new var to envp
*/

int	realloc_and_add_var_to_envp(t_shell *shell, char *var, char ***envp)
{
	char	**temp_envp;
	char	**old;
	int		i;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	temp_envp = malloc((i + 2) * sizeof(char *));
	if (!temp_envp)
		return (ms_error_fail(shell, 1, "realloc_and_add_var...", "malloc()"));
	i = 0;
	while ((*envp)[i] != NULL)
	{
		temp_envp[i] = ft_strdup((*envp)[i]);
		if (!temp_envp[i])
			return (ms_error_fail(shell, 1, "realloc_and_add...", "ft_strdup"));
		i++;
	}
	temp_envp[i] = ft_strdup(var);
	if (!temp_envp[i])
		return (ms_error_fail(shell, 1, "realloc_and_add_var...", "malloc()"));
	temp_envp[i + 1] = NULL;
	old = *envp;
	*envp = temp_envp;
	return (free_arguments(old));
}

bool	contains_invalid_identifier(char *var)
{
	int	i;

	if (var[0] == '\0' || var[0] == ' ')
		return (true);
	if (var[0] >= '0' && var[0] <= '9')
		return (true);
	if (var[0] == '=')
		return (true);
	i = 0;
	while (var[i] != '=' && var[i] != '\0')
	{
		if (var[i] == '.' || var[i] == '-')
			return (true);
		i++;
	}
	return (false);
}

bool	var_has_no_assignment(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '=')
			return (false);
		i++;
	}
	return (true);
}

int	export_arg(t_shell *shell, char *var, char ***envp)
{
	int	i;
	int	export_list_i;

	if (contains_invalid_identifier(var) == true)
		return (ms_error_export(shell, 2, var));
	if (var_has_no_assignment(var))
		return (export_var_no_assign(shell, var, &(shell->export_list), *envp));
	i = find_env_index(var, get_var_len(var), *envp);
	if (i < 0)
	{
		export_list_i = find_export_i(var, shell->export_list);
		if (export_list_i != -42)
			realloc_and_del_1_envp(shell, &(shell->export_list), export_list_i);
		return (realloc_and_add_var_to_envp(shell, var, envp));
	}
	else
		return (update_var(var, envp));
}

int	exec_export(t_shell *shell, t_node *node, char ***envp)
{
	int		i;
	char	*var;
	int		temp_exit_code;
	int		exit_code;

	exit_code = 0;
	if (!node->args[1])
		return (print_export_list(shell, shell->export_list, *envp));
	i = 1;
	while (node->args[i] != NULL)
	{
		var = node->args[i];
		temp_exit_code = export_arg(shell, var, envp);
		if (temp_exit_code != 0)
			exit_code = temp_exit_code;
		i++;
	}
	return (exit_code);
}
