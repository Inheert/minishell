/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:09:05 by cluby             #+#    #+#             */
/*   Updated: 2024/10/05 22:34:19 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*t_token_last(t_token *lst)
{
	t_token	*temp;
	int		last;
	int		i;

	temp = lst;
	last = t_token_size(temp) - 1;
	i = 0;
	while (i++ < last)
		temp = temp->next;
	return (temp);
}

void	t_token_display(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		fprintf(stderr, "[%d] %s\n", lst->token, lst->str);
		lst = lst->next;
	}
	fprintf(stderr, "\n");
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
