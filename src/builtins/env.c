/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:12 by Théo              #+#    #+#             */
/*   Updated: 2024/08/28 15:50:55 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **menvp)
{
	int	i;

	if (!menvp || !*menvp)
		return ;
	i = -1;
	while (menvp[++i])
	{
		if (!ft_strchr(menvp[i], '='))
			continue ;
		ft_putstr_fd(menvp[i], 1);
		write(1, "\n", 1);
	}
}
