/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:41:02 by hallison          #+#    #+#             */
/*   Updated: 2025/07/04 16:03:01 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_core.h"

int	ms_start_minishell(t_shell *shell)
{
	sig_set_scope(shell, SIGSCOPE_INTERACTIVE);
	while (1)
	{
		g_sig_in_prompt = false;
		in_input_loop(shell);
		if (g_sig_in_prompt)
			shell->last_exit_code = 130;
		if (!shell->input)
			break ;
		tok_tokenize(shell);
		gc_cleanup(&shell->input_mem);
		shell->ast = parse_tokens(shell, shell->tokens, NULL);
		if (!shell->ast)
			shell->in_status = IN_ERROR;
		heredoc_start(shell, shell->ast);
		gc_cleanup(&shell->parser_mem);
		if (shell->in_status != IN_ERROR)
			shell->last_exit_code = start_exec(shell->ast, &shell->envp, shell);
		heredoc_unlink_all(shell->ast);
		gc_cleanup(&shell->exec_mem);
		ms_reset_shell_state(shell);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (!envp)
	{
		ft_putstr_fd("Error: Missing envp as an argument to main\n", 2);
		return (1);
	}
	if (argc != 1)
	{
		return (printf("Error: minishell doesn't take arguments\n"));
		return (1);
	}
	ms_init_shell(envp, &shell);
	ms_start_minishell(&shell);
	(void)argv;
	gc_cleanup_shell(&shell);
	return (0);
}
