/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/25 12:31:53 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*input_manager(t_envp *menvp)
{
	char	*line;
	char	**lexer;
	t_token	*tokens;

	line = readline("minishell$ ");
	if (!line)
		return (raise_error("exit", NULL, 1, 0), NULL);
	if (ft_strlen(line) < 1)
		return (NULL);
	add_history(line);
	lexer = manage_lexer(line);
	if (!lexer)
		return (NULL);
	free(line);
	tokens = process_quotes(lexer, menvp);
	if (find_token_type(&tokens, menvp) == -1)
		return (free_t_token(tokens),
			raise_error("Parsing", "Invalid redirection.", 0, 1), NULL);
	if (!concat_token_redir(&tokens) || tokens == 0 || tokens->token == 0
		|| t_token_last(tokens)->token == 0)
		return (free_t_token(tokens),
			raise_error("Parsing", "Invalid redirection or pipe at the start.",
				0, 1), NULL);
	return (tokens);
}

int	g_signal_code = 0;

int	main(int argc, char **argv, char **envp)
{
	struct termios	termios;
	t_envp			*menvp;
	t_token			*tokens;

	set_exit_status(0, &menvp);
	menvp = t_envp_init(envp);
	if (tcgetattr(STDIN_FILENO, &termios) == 0)
	{
		termios.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	}
	else
		raise_perror("tcgetattr failed", 1);
	rl_catch_signals = 0;
	while (1)
	{
		set_signals(READLINE);
		tokens = input_manager(menvp);
		if (!tokens)
			continue ;
		command_line_exec(&tokens, &menvp);
	}
	return ((void)argc, (void)argv, 0);
}
