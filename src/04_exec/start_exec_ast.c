/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:04:37 by hallison          #+#    #+#             */
/*   Updated: 2025/06/25 20:29:32 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

int	handle_built_in(t_node *node, char ***envp, t_shell *shell)
{
	if (node->arg_zero == IS_CD)
		return (exec_cd(shell, node, envp));
	if (node->arg_zero == IS_ECHO)
		return (exec_echo(node));
	if (node->arg_zero == IS_EXPORT)
		return (exec_export(shell, node, envp));
	if (node->arg_zero == IS_ENV)
		return (exec_env(node, *envp));
	if (node->arg_zero == IS_PWD)
		return (exec_pwd(shell));
	if (node->arg_zero == IS_UNSET)
		return (exec_unset(shell, node, envp));
	if (node->arg_zero == IS_EXIT)
		return (ms_exit(shell, node));
	return (127);
}

int	exec_bonus(t_shell *shell, t_node *ast, char ***envp)
{
	int	exit_code;

	exit_code = 127;
	if (ast->arg_zero == IS_AND)
	{
		exit_code = start_exec(ast->left, envp, shell);
		if (exit_code == 0)
			exit_code = start_exec(ast->right, envp, shell);
	}
	else if (ast->arg_zero == IS_OR)
	{
		exit_code = start_exec(ast->left, envp, shell);
		if (exit_code != 0)
			exit_code = start_exec(ast->right, envp, shell);
	}
	return (exit_code);
}

int	handle_operator(t_node *ast, char ***envp, t_shell *shell)
{
	int	exit_code;

	exit_code = 127;
	if (ast->op_prec == PREC_SUBSHELL)
		exit_code = start_exec(ast->left, envp, shell);
	else if (ast->arg_zero == IS_PIPE)
		exit_code = open_pipe(ast, envp, shell);
	else if (ast->arg_zero == IS_AND || ast->arg_zero == IS_OR)
		exit_code = (exec_bonus(shell, ast, envp));
	return (exit_code);
}

int	set_arg_zero_code(char *cmd)
{
	if (!cmd)
		return (0);
	if (strncmp(cmd, "cd", 3) == 0)
		return (IS_CD);
	if (strncmp(cmd, "export", 7) == 0)
		return (IS_EXPORT);
	if (strncmp(cmd, "echo", 5) == 0)
		return (IS_ECHO);
	if (strncmp(cmd, "env", 4) == 0)
		return (IS_ENV);
	if (strncmp(cmd, "pwd", 4) == 0)
		return (IS_PWD);
	if (strncmp(cmd, "unset", 6) == 0)
		return (IS_UNSET);
	if (strncmp(cmd, "exit", 5) == 0)
		return (IS_EXIT);
	if (strncmp(cmd, "|", 2) == 0)
		return (IS_PIPE);
	if (strncmp(cmd, "&&", 3) == 0)
		return (IS_AND);
	if (strncmp(cmd, "||", 3) == 0)
		return (IS_OR);
	return (0);
}

int	start_exec(t_node *ast, char ***envp, t_shell *shell)
{
	int		exit_code;

	exit_code = 0;
	sig_set_scope(shell, SIGSCOPE_EXTERN);
	if (!ast)
		return (0);
	ast->arg_zero = set_arg_zero_code(ast->cmd);
	if (ast->arg_zero == IS_PIPE || ast->arg_zero == IS_AND
		|| ast->arg_zero == IS_OR || ast->op_prec == PREC_SUBSHELL)
		exit_code = handle_operator(ast, envp, shell);
	else
	{
		if (ast->redirections != NULL)
			exit_code = exec_redir(ast, envp, shell);
		else
		{
			if (ast->arg_zero != 0)
				exit_code = handle_built_in(ast, envp, shell);
			else
				exit_code = handle_external(shell, ast, *envp);
		}
	}
	if (shell->fatal == true)
		ms_clean_exit(shell, exit_code, true);
	return (exit_code);
}
