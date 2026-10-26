/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:38:46 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:18:37 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_core.h"

//global variable:
bool	g_sig_in_prompt = false;

void	sig_exit_error(t_shell *shell, int code)
{
	printf("Error setting up signal handling, exiting minishell...\n");
	ms_clean_exit(shell, code, true);
}

static void	sig_simple_sigaction(t_shell *shell, struct sigaction *s_sigact, \
						void (*sig_handler)(int), int signum)
{
	if (sigemptyset(&s_sigact->sa_mask) == -1)
		sig_exit_error(shell, 1);
	s_sigact->sa_flags = 0;
	s_sigact->sa_handler = sig_handler;
	if (sigaction(signum, s_sigact, NULL) == -1)
		sig_exit_error(shell, 1);
}

void	sig_handle_prompt(int signum)
{
	(void)signum;
	g_sig_in_prompt = true;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handle_heredoc(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	sig_set_scope(t_shell *shell, int type)
{
	struct sigaction	s_sa_int;
	struct sigaction	s_sa_quit;

	if (type == SIGSCOPE_INTERACTIVE)
	{
		sig_simple_sigaction(shell, &s_sa_quit, SIG_IGN, SIGQUIT);
		sig_simple_sigaction(shell, &s_sa_int, sig_handle_prompt, SIGINT);
	}
	else if (type == SIGSCOPE_HEREDOC)
	{
		sig_simple_sigaction(shell, &s_sa_quit, SIG_IGN, SIGQUIT);
		sig_simple_sigaction(shell, &s_sa_int, sig_handle_heredoc, SIGINT);
	}
	else if (type == SIGSCOPE_EXTERN)
	{
		sig_simple_sigaction(shell, &s_sa_quit, SIG_IGN, SIGQUIT);
		sig_simple_sigaction(shell, &s_sa_int, SIG_IGN, SIGINT);
	}
	else if (type == SIGSCOPE_EXEC)
	{
		sig_simple_sigaction(shell, &s_sa_quit, SIG_DFL, SIGQUIT);
		sig_simple_sigaction(shell, &s_sa_int, SIG_DFL, SIGINT);
	}
}
