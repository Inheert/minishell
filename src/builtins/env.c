/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:12 by Théo              #+#    #+#             */
/*   Updated: 2024/10/06 01:18:35 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_processus *process, t_envp *menvp)
{
	if (!menvp)
		return ;
	while (menvp)
	{
		if (!menvp->equal && !menvp->value)
		{
			menvp = menvp->next;
			continue ;
		}
		ft_putstr_fd(menvp->name, get_fds(process, STDOUT_FILENO));
		if (menvp->equal && !menvp->value)
			ft_putendl_fd("=\n", get_fds(process, STDOUT_FILENO));
		else
		{
			ft_putstr_fd("=", get_fds(process, STDOUT_FILENO));
			ft_putendl_fd(menvp->value, get_fds(process, STDOUT_FILENO));
		}
		menvp = menvp->next;
	}
}
