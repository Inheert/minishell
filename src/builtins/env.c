/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:12 by Théo              #+#    #+#             */
/*   Updated: 2024/10/09 18:01:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_processus *process, t_envp *menvp)
{
	if (!menvp)
		return ;
	while (menvp)
	{
		if ((!menvp->equal && !menvp->value)
			|| ft_strcmp(menvp->name, "?") == 0)
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
	set_exit_status(0, NULL);
}
