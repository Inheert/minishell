/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:31 by Théo              #+#    #+#             */
/*   Updated: 2024/09/08 15:47:45 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_envp *menvp, char *to_unset)
{
	if (!to_unset || !menvp)
		return ;
	while (menvp)
	{
		if (ft_strcmp(menvp->name, to_unset) == 0)
		{
			if (menvp->prev)
				menvp->prev->next = menvp->next;
			if (menvp->next)
				menvp->next->prev = menvp->prev;
		}
		menvp = menvp->next;
	}
}
