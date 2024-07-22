/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:09:05 by cluby             #+#    #+#             */
/*   Updated: 2024/07/16 16:24:41 by cluby            ###   ########.fr       */
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
