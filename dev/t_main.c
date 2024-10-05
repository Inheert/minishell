/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 01:34:39 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_envp	*menvp;
	t_token	*token;
	char	*path;
	char	*prompt;
	char	*tmp;

	(void)argc;
	(void)argv;
	menvp = t_envp_init(envp);
	while (1)
	{
		path = getcwd(NULL, 0);
		tmp = path;
		ft_store_malloc(tmp);
		path = ft_strjoin(path, " $ ");
		prompt = readline(path);
		if (!prompt)
			break ;
		ft_store_malloc(prompt);
		add_history(prompt);
		token = tokenisation(prompt);
		ft_free((ft_free(tmp), ft_free(path), prompt));
		if (!parse_tokens(token, menvp))
			return (printf("Syntax error\n"), 0);
		join_tokens(token);
		clean_blank(&token);
		put_cmd(token);
		command_line_exec(&token, menvp);
	}
	ft_free_all();
	return (0);
}
