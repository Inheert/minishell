/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:09:51 by Théo              #+#    #+#             */
/*   Updated: 2024/09/21 09:10:29 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_signals_handlers(int sig)
{

	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		ft_free_all();
		exit(0);
	}
}

void	init_parent_signals_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = &parent_signals_handlers;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	children_signals_handlers(int sig)
{
	printf("zpo,ge");
	if (sig == SIGINT)
	{
		printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("exit\n");
	}
}

void	init_children_signals_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = &children_signals_handlers;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	printf("Init\n");
}
