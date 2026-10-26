/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:53:28 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:00:34 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h" // TODO - Should auto_export stay in exec?
#include "ms_core.h"

void	copy_envp(char **original_envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (original_envp[i] != NULL)
		i++;
	shell->envp = malloc((i + 1) * sizeof(char *));
	if (!shell->envp)
	{
		ms_error_fail(shell, 1, "copy_envp()", "malloc()");
		ms_clean_exit(shell, 1, true);
	}
	i = 0;
	while (original_envp[i] != NULL)
	{
		shell->envp[i] = ft_strdup(original_envp[i]);
		if (!(shell->envp[i]))
		{
			ms_error_fail(shell, 1, "copy_envp()", "malloc()");
			ms_clean_exit(shell, 1, true);
		}
		i++;
	}
	shell->envp[i] = NULL;
}

char	**init_export_list(t_shell *shell)
{
	char	**export_list;

	export_list = malloc(sizeof(char *));
	if (!export_list)
	{
		ms_error_fail(shell, 1, "copy_envp()", "malloc()");
		ms_clean_exit(shell, 1, true);
	}
	export_list[0] = NULL;
	return (export_list);
}

void	increment_shell_level(t_shell *shell, char ***envp)
{
	char	*old_num;
	int		old_int;
	char	*new_shlvl;
	char	*new_assign;

	old_num = get_str_from_envp("SHLVL=", *envp);
	if (old_num == NULL)
		return ;
	old_int = ft_atoi(old_num);
	new_shlvl = ft_itoa(old_int + 1);
	if (!new_shlvl)
		return ;
	new_assign = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	if (!new_assign)
	{
		ms_error_fail(shell, 1, "increment_shell_level()", "malloc()");
		ms_clean_exit(shell, 1, true);
	}
	auto_export(shell, new_assign, envp);
	free(new_assign);
	return ;
}

void	ms_init_shell(char **envp, t_shell *shell)
{
	if (!shell)
		return ;
	ft_bzero(shell, sizeof(t_shell));
	gc_init(&shell->input_mem);
	gc_init(&shell->parser_mem);
	gc_init(&shell->exec_mem);
	copy_envp(envp, shell);
	increment_shell_level(shell, &shell->envp);
	shell->export_list = init_export_list(shell);
	shell->fatal = false;
	shell->prev_read_fd = -42;
	if (getcwd(shell->protected_cwd, PATH_MAX + 1) == NULL)
		perror("Error");
}

void	ms_reset_shell_state(t_shell *shell)
{
	shell->ast = NULL;
	shell->buffer = NULL;
	shell->tokens = NULL;
	sig_set_scope(shell, SIGSCOPE_INTERACTIVE);
}
