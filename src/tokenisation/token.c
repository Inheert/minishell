/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:49:29 by cluby             #+#    #+#             */
/*   Updated: 2024/07/11 20:21:14 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenization(char *argv)
{
	int	i;
	int	j;
	t_token	*token;

	token = NULL;
	i = 0;
	j = 0;
	while (argv[i])
	{
		while (argv[i] == ' ' || argv[i] == '\t')
			i++;
		if (argv[i] == '\'')
		{
			i++;
			j = i;
			while(argv[i] != '\'')
				i++;
			printf("test1\n");
			if (token)
				ft_token_add_back(&token, ft_token_new(ft_substr(argv, j, i - j), STRING));
			else
				token = ft_token_new(ft_substr(argv, j, i - j), STRING);
			//new token STRING
			//add token if needed	
		}
		/* if (argv[i] == '"')
		{
			i++;
			j = i;
			while(argv[i] != '"')
				i++;
			//new token STRING_VAR
			//add token if needed		
		}
		if (argv[i] == '|')
		{
			//new token PIPE
			//add token if needed
			i++;
		} */
		i++;
	}
	return (token);
}
