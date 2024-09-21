/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:11:56 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/21 20:06:07 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_envp	*menvp;
	t_token	*token;
	char	*path;
	char	*prompt;

	(void)argc;
	(void)argv;
	menvp = t_envp_init(envp);
	while (1)
	{
		path = getcwd(NULL, 0);
		path = ft_strjoin(path, " $ ");
		prompt = readline(path);
		add_history(prompt);
		token = tokenisation(prompt);
		if (!parse_tokens(token, menvp))
			return (printf("Syntax error\n"), 0);
		join_tokens(token);
		clean_blank(&token);
		put_cmd(token);
		ft_exec(&token, menvp);
	}
}
