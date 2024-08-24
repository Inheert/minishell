/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/24 13:50:03 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tester(char **envp)
{
	t_token	*tokens;

	printf("FIRST TEST:\n\n");

	tokens = ft_token_new("infile", REDIR_IN);
	ft_token_add_back(&tokens, ft_token_new("aff", COMMAND));
	ft_token_add_back(&tokens, ft_token_new("abc", STRING));
	ft_token_add_back(&tokens, ft_token_new("infile2", REDIR_IN));
	ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	ft_token_add_back(&tokens, ft_token_new("wc", COMMAND));
	//ft_token_add_back(&tokens, ft_token_new("outfile", REDIR_OUT));
	ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	ft_token_add_back(&tokens, ft_token_new("cat", COMMAND));
	ft_exec(&tokens, envp);
	ft_free_all();

	usleep(10000);

	// ft_putstr_fd("\n------------------------------\n", 0);

	// ft_putstr_fd("SECOND TEST:\n", 0);

	// tokens = ft_token_new("ls", COMMAND);
	// ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	// ft_token_add_back(&tokens, ft_token_new("cat", COMMAND));
	// ft_exec(&tokens, envp);
	// ft_free_all();

	usleep(10000);

	ft_putstr_fd("\n------------------------------\n", 0);

	ft_putstr_fd("THIRD TEST:\n\n", 0);

	tokens = NULL;
	ft_token_add_back(&tokens, ft_token_new("ls", COMMAND));
	ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	ft_token_add_back(&tokens, ft_token_new("test", HERE_DOC));
	ft_token_add_back(&tokens, ft_token_new("cat", COMMAND));
	ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	ft_token_add_back(&tokens, ft_token_new("wc", COMMAND));
	ft_exec(&tokens, envp);
	ft_free_all();

	usleep(10000);

	ft_putstr_fd("\\nn------------------------------\n", 0);

	ft_putstr_fd("FOURTH TEST:\n\n", 0);

	tokens = NULL;
	ft_token_add_back(&tokens, ft_token_new("infile", REDIR_IN));
	ft_token_add_back(&tokens, ft_token_new("cat", COMMAND));
	ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	ft_token_add_back(&tokens, ft_token_new("wc", COMMAND));
	ft_token_add_back(&tokens, ft_token_new(NULL, PIPE));
	ft_token_add_back(&tokens, ft_token_new("cat", COMMAND));
	ft_token_add_back(&tokens, ft_token_new("outfile", REDIR_OUT));
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
