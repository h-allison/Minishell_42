/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:28:31 by hallison          #+#    #+#             */
/*   Updated: 2025/04/09 14:28:52 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	exec_env(t_node *node, char **envp)
{
	int	i;

	if (node->args[0] && node->args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd("': No such file or directory.\n", 2);
		return (127);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
