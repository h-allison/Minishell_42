/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_print_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:02:50 by hallison          #+#    #+#             */
/*   Updated: 2025/05/29 16:02:51 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

/*
	Functions for printing the full export list,
	when "export" is entered as a command with no arguments.

	The printed list includes all exported variables,
	including those with an assignment (everything in envp)
	and those without (in minishell, node->export_list)

*/

char	*print_next_alphabetical(char **list, int len, int **tracked)
{
	int		i;
	char	*next;
	int		next_i;
	int		*tracking;

	i = 0;
	tracking = *tracked;
	while (i < len && tracking[i] == 1)
		i++;
	if (i >= len)
		return (NULL);
	next = list[i];
	next_i = i;
	i = 0;
	while (i < len)
	{
		if ((tracking[i] != 1) && (ft_strcmp(list[i], next) < 0))
		{
			next = list[i];
			next_i = i;
		}
		i++;
	}
	tracking[next_i] = 1;
	return (next);
}

int	*init_already_printed(t_shell *shell, int len)
{
	int	*printed_or_not;
	int	i;

	printed_or_not = malloc((len) * sizeof(int));
	if (!printed_or_not)
	{
		ms_error_fail(shell, 1, "init_already_printed()", "malloc()");
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		printed_or_not[i] = 0;
		i++;
	}
	return (printed_or_not);
}

void	print_export_alphabetical(t_shell *shell, char **print_list, int len)
{
	int			print_count;
	int			*already_printed;
	char		*print;

	already_printed = init_already_printed(shell, len);
	if (!already_printed)
		return ;
	print_count = 0;
	while (print_count < len)
	{
		print = print_next_alphabetical(print_list, len, &already_printed);
		if (print && ft_strncmp(print, "declare -x _=", 13) != 0)
			printf("%s\n", print);
		print_count++;
	}
	free(already_printed);
}
