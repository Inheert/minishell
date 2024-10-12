/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:09:05 by cluby             #+#    #+#             */
/*   Updated: 2024/10/12 15:06:38 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*t_token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	**t_token_to_str_ptr(t_token *lst)
{
	char			**ptr;
	unsigned int	size;
	unsigned int	i;

	size = t_token_size(lst);
	ptr = ft_malloc(sizeof(char *) * (size + 1));
	ptr[size] = NULL;
	i = 0;
	while (lst)
	{
		ptr[i++] = lst->str;
		lst = lst->next;
	}
	return (ptr);
}

void	print_lexer(char *line, char **lexer)
{
	int		i;

	i = 0;
	printf("\n\033[37mInput: [%s]\033[0m\n\033[33mLexer:\033[0m ", line);
	while (lexer && lexer[i])
	{
		printf("\033[33m[%s]\33[0m ", lexer[i]);
		i++;
	}
	printf("\n\n");
}

void	t_token_display(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("[%d] [%d] %s\n", lst->token, lst->flag_quotes,
			lst->str);
		lst = lst->next;
	}
	printf("\n");
}
