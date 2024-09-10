/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 16:47:54 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tester(char **envp)
{
	t_token	*tokens;

	printf("FIRST TEST:\n\n");

	tokens = t_token_new("infile", REDIR_IN);
	t_token_add_back(&tokens, t_token_new("aff", COMMAND));
	t_token_add_back(&tokens, t_token_new("abc", STRING));
	t_token_add_back(&tokens, t_token_new("infile2", REDIR_IN));
	t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	t_token_add_back(&tokens, t_token_new("wc", COMMAND));
	//t_token_add_back(&tokens, t_token_new("outfile", REDIR_OUT));
	t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	t_token_add_back(&tokens, t_token_new("cat", COMMAND));
	ft_exec(&tokens, envp);
	ft_free_all();

	usleep(10000);

	// ft_putstr_fd("\n------------------------------\n", 0);

	// ft_putstr_fd("SECOND TEST:\n", 0);

	// tokens = t_token_new("ls", COMMAND);
	// t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	// t_token_add_back(&tokens, t_token_new("cat", COMMAND));
	// ft_exec(&tokens, envp);
	// ft_free_all();

	usleep(10000);

	ft_putstr_fd("\n------------------------------\n", 0);

	ft_putstr_fd("THIRD TEST:\n\n", 0);

	tokens = NULL;
	t_token_add_back(&tokens, t_token_new("ls", COMMAND));
	t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	t_token_add_back(&tokens, t_token_new("test", HERE_DOC));
	t_token_add_back(&tokens, t_token_new("cat", COMMAND));
	t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	t_token_add_back(&tokens, t_token_new("wc", COMMAND));
	ft_exec(&tokens, envp);
	ft_free_all();

	usleep(10000);

	ft_putstr_fd("\\nn------------------------------\n", 0);

	ft_putstr_fd("FOURTH TEST:\n\n", 0);

	tokens = NULL;
	t_token_add_back(&tokens, t_token_new("infile", REDIR_IN));
	t_token_add_back(&tokens, t_token_new("cat", COMMAND));
	t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	t_token_add_back(&tokens, t_token_new("wc", COMMAND));
	t_token_add_back(&tokens, t_token_new(NULL, PIPE));
	t_token_add_back(&tokens, t_token_new("cat", COMMAND));
	t_token_add_back(&tokens, t_token_new("outfile", REDIR_OUT));
	ft_exec(&tokens, envp);
	ft_free_all();
}

int	main(int argc, char **argv, char **envp)
{
	tester(envp);
	argc = (int)argc;
	argv = (char **)argv;
	return (0);
}
