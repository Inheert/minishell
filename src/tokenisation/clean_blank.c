/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_blank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:25:23 by cluby             #+#    #+#             */
/*   Updated: 2024/09/15 23:39:59 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_blank(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->token == BLANK)
		{
			if (tmp->next || tmp->prev)
			{
				t_token_del(token, tmp);
				tmp = *token;
			}
			else
			{
				t_token_del(token, tmp);
				return ;
			}
		}
		tmp = tmp->next;
	}
}
