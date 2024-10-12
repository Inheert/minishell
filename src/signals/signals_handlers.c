/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:09:51 by Théo              #+#    #+#             */
/*   Updated: 2024/10/11 10:36:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_code = SIGINT;
	}
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_code = SIGINT;
		write(STDOUT_FILENO, "^C\n", 3);
	}
	if (signum == SIGQUIT)
		g_signal_code = SIGQUIT;
}

void	heredoc_sigaction_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	fork_signal_handler(int signum)
{
	if (signum == SIGINT)
		g_signal_code = SIGINT;
	if (signum == SIGQUIT)
		g_signal_code = SIGQUIT;
}

void	set_signals(t_signal_type mode)
{
	if (mode == READLINE)
	{
		signal(SIGINT, readline_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == FORK)
	{
		signal(SIGINT, fork_signal_handler);
		signal(SIGQUIT, fork_signal_handler);
	}
	else if (mode == SILENCE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC_SIG)
	{
		heredoc_sigaction_handler();
		signal(SIGQUIT, SIG_IGN);
	}
}
