/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/22 11:20:05 by tclaereb         ###   ########.fr       */
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
		ft_exec(&token, menvp);
	}
	ft_free_all();
	return (0);
}
