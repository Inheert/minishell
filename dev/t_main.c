/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:48:50 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 18:48:51 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	tester(t_envp *menvp)
{
	t_token	*token;

	token = NULL;
	t_token_add_back(&token, t_token_new("infile", REDIR_IN));
	t_token_add_back(&token, t_token_new("cat", COMMAND));
	t_token_add_back(&token, t_token_new("outfile", REDIR_OUT));
	t_token_add_back(&token, t_token_new(NULL, PIPE));
	t_token_add_back(&token, t_token_new("cat", COMMAND));
	t_token_add_back(&token, t_token_new(NULL, PIPE));
	t_token_add_back(&token, t_token_new("dd", HEREDOC));
	t_token_add_back(&token, t_token_new("cat", COMMAND));
	command_line_exec(&token, menvp);
}

void	update_shell_level(t_envp **menvp)
{
	t_envp	*tmp;
	int		shlvl;

	tmp = t_envp_finding(*menvp, "SHLVL");
	if (!tmp)
	{
		tmp = t_envp_new("SHLVL", "1", 0);
		t_envp_add_back(menvp, tmp);
		return ;
	}
	shlvl = ft_atoi(tmp->value);
	if (shlvl >= 0 && shlvl < 1000)
		tmp->value = ft_itoa(shlvl + 1);
	else
		tmp->value = "1";
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*menvp;
	t_token	*token;
	char	*path;
	char	*prompt;
	char	*tmp;
	int		exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	menvp = t_envp_init(envp);
	return (tester(menvp), 0);
	update_shell_level(&menvp);
	while (1)
	{
		t_envp_check(menvp);
		init_parent_signals_handlers();
		path = getcwd(NULL, 0);
		tmp = path;
		ft_store_malloc(tmp);
		path = ft_strjoin(path, " $ ");
		prompt = readline(path);
		if (!prompt)
			ft_exit(NULL, 0);
		ft_store_malloc(prompt);
		add_history(prompt);
		token = tokenisation(prompt);
		ft_free((ft_free(tmp), ft_free(path), prompt));
		if (!parse_tokens(&token, menvp))
			return (printf("Syntax error\n"), 0);
		join_tokens(token);
		clean_blank(&token);
		put_cmd(&token);
		exit_status = command_line_exec(&token, menvp);
	}
	ft_free_all();
	return (exit_status);
}
