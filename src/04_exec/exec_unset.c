/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:35:11 by hallison          #+#    #+#             */
/*   Updated: 2025/04/09 18:35:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

void	reassign_nodes(char ***envp, char ***temp_envp, int del_i, int old_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < old_len - 1)
	{
		if (j == del_i)
		{
			j++;
		}
		else
		{
			(*temp_envp)[i] = (*envp)[j];
			j++;
			i++;
		}
	}
	(*temp_envp)[i] = NULL;
}

int	realloc_and_del_1_envp(t_shell *shell, char ***envp, int delete_i)
{
	char	**temp_envp;
	char	**old;
	int		old_len;
	int		i;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	old_len = i;
	if (delete_i < 0 || delete_i >= old_len)
		return (1);
	free((*envp)[delete_i]);
	temp_envp = malloc((old_len) * sizeof(char *));
	if (!temp_envp)
		return (ms_error_fail(shell, 1, "realloc_and_delete...", "malloc()"));
	reassign_nodes(envp, &temp_envp, delete_i, old_len);
	old = *envp;
	*envp = temp_envp;
	free(old);
	return (0);
}

int	exec_unset(t_shell *shell, t_node *node, char ***envp)
{
	int	args_i;
	int	env_i;
	int	export_i;

	args_i = 1;
	while (node->args[args_i] != NULL)
	{
		env_i = find_env_index_2(node->args[args_i], *envp);
		if (env_i != -42)
			realloc_and_del_1_envp(shell, envp, env_i);
		else
		{
			export_i = find_export_i(node->args[args_i], shell->export_list);
			if (export_i != -42)
				realloc_and_del_1_envp(shell, &(shell->export_list), export_i);
		}
		args_i++;
	}
	return (0);
}
