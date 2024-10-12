/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:31 by Théo              #+#    #+#             */
/*   Updated: 2024/10/09 18:01:16 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_top_of_the_chain(t_envp **menvp, char *to_unset)
{
	t_envp	*tmp;

	if (ft_strcmp((*menvp)->name, to_unset) != 0)
		return (0);
	tmp = *menvp;
	*menvp = (*menvp)->next;
	(*menvp)->prev = NULL;
	free_t_envp(tmp);
	return (1);
}

static void	unset_var_in_chain(t_envp *menvp, char *to_unset)
{
	if (ft_strcmp(to_unset, "?") == 0)
		return ;
	while (menvp)
	{
		if (ft_strcmp(menvp->name, to_unset) == 0)
		{
			if (menvp->prev)
				menvp->prev->next = menvp->next;
			if (menvp->next)
				menvp->next->prev = menvp->prev;
			free_t_envp(menvp);
			break ;
		}
		menvp = menvp->next;
	}
}

void	ft_unset(t_envp **menvp, char **to_unset)
{
	int		i;

	if (!to_unset || !menvp)
		return ;
	i = -1;
	while (to_unset[++i])
	{
		if (unset_top_of_the_chain(menvp, to_unset[i]))
			continue ;
		unset_var_in_chain(*menvp, to_unset[i]);
	}
	set_exit_status(0, NULL);
}
