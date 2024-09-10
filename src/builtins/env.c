/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:12 by Théo              #+#    #+#             */
/*   Updated: 2024/09/10 17:36:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp *menvp)
{
	if (!menvp)
		return ;
	while (menvp)
	{
		if (!menvp->equal && !menvp->value)
		{
			menvp = menvp->next;
			continue;
		}
		printf("%s", menvp->name);
		if (menvp->equal && !menvp->value)
			printf("=\n");
		else
			printf("=%s\n", menvp->value);
		menvp = menvp->next;
	}
}
