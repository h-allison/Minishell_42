/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_print_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:47:14 by hallison          #+#    #+#             */
/*   Updated: 2025/06/24 13:47:15 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	envp_and_export_len(char **export_list, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (export_list[i] != NULL)
	{
		while (export_list[i] != NULL)
			i++;
	}
	if (envp[j] != NULL)
	{
		while (envp[j] != NULL && envp[j][0] != '\0')
			j++;
	}
	return (i + j);
}

/*
	copy_into_new_list() is called twice to copy contents of 
	1) envp
	2) "invisble" export list
	into the list to be printed by the command "export"
*/

int	copy_into_new_list(char **print_list, char **source, int j)
{
	int	i;

	i = 0;
	while (source[i] != NULL)
	{
		if (source[i][0] != ' ')
		{
			print_list[j] = ft_strjoin("declare -x ", source[i]);
			if (!print_list[j])
			{
				free_list_on_error(print_list, j);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (j);
}

char	**combine_lists(char **export_list, char **envp, int total_list_len)
{
	int		j;
	char	**print_list;

	print_list = malloc(total_list_len * sizeof(char *));
	if (!print_list)
		return (NULL);
	j = (copy_into_new_list(print_list, envp, 0));
	if (j == -1)
		return (NULL);
	if (copy_into_new_list(print_list, export_list, j) == -1)
		return (NULL);
	return (print_list);
}

int	print_export_list(t_shell *shell, char **export_list, char **envp)
{
	char	**print_list;
	int		total_list_len;
	int		i;

	if (envp[0] == NULL && export_list[0] == NULL)
		return (1);
	total_list_len = envp_and_export_len(export_list, envp);
	print_list = combine_lists(export_list, envp, total_list_len);
	if (print_list == NULL)
		return (ms_error_fail(shell, 1, "combine_lists()", "malloc()"));
	print_export_alphabetical(shell, print_list, total_list_len);
	i = 0;
	while (i < total_list_len)
	{
		free (print_list[i]);
		i++;
	}
	free(print_list);
	return (0);
}
