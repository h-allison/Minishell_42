/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:54:42 by hallison          #+#    #+#             */
/*   Updated: 2025/07/08 12:15:33 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_arguments(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i] != NULL)
	{
		free(arguments[i]);
		i++;
	}
	free(arguments);
	return (0);
}

/*
	free_list_on_error()
	iterates backwards through an array of strings,
	frees each, then frees the array
*/

void	free_list_on_error(char **print_list, int j)
{
	perror("Error");
	while (j >= 0)
	{
		free(print_list[j]);
		j--;
	}
	free(print_list);
	return ;
}
