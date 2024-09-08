/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:12 by Théo              #+#    #+#             */
/*   Updated: 2024/09/08 16:09:33 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp *menvp)
{
	if (!menvp)
		return ;
	while (menvp)
	{
		ft_putstr_fd(menvp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(menvp->value, 1);
		write(1, "\n", 1);
		menvp = menvp->next;
	}
}
