/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:09:05 by cluby             #+#    #+#             */
/*   Updated: 2024/08/23 15:37:39 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token *lst)
{
	t_token	*temp;
	int		last;
	int		i;

	temp = lst;
	last = token_ptr_size(temp) - 1;
	i = 0;
	while (i++ < last)
		temp = temp->next;
	return (temp);
}

void	display_tokens(t_token *lst)
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

char	**token_struct_to_str_ptr(t_token *lst)
{
	char			**ptr;
	unsigned int	size;
	unsigned int	i;

	size = token_ptr_size(lst);
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
