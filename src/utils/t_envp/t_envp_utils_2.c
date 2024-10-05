/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:37:42 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/05 18:26:14 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_envp_display(t_envp *menvp)
{
	while (menvp)
	{
		fprintf(stderr, "NAME: %s\nVALUE: %s\n\n", menvp->name, menvp->value);
		menvp = menvp->next;
	}
}

char	*concat_str_equal_sign(char **str)
{
	char	*tmp;
	char	*buff;
	int		i;

	tmp = NULL;
	i = 0;
	while (str[++i])
	{
		if (!tmp)
			tmp = str[i];
		else
		{
			buff = tmp;
			tmp = ft_strjoin(tmp, str[i]);
			ft_free(buff);
			ft_free(str[i]);
		}
		if (str[i + 1])
		{
			buff = tmp;
			tmp = ft_strjoin(tmp, "=");
			ft_free(buff);
		}
	}
	return (tmp);
}

int	t_envp_is_exist(t_envp *menvp, char *name)
{
	if (!menvp || !name)
		return (0);
	while (menvp)
	{
		if (ft_strcmp(menvp->name, name) == 0)
			return (1);
		menvp = menvp->next;
	}
	return (0);
}

static void	t_envp_update_2(t_envp *menvp, t_envp *new)
{
	while (menvp)
	{
		if (ft_strcmp(menvp->name, new->name) == 0)
		{
			if (menvp->prev)
				menvp->prev->next = new;
			if (menvp->next)
				menvp->next->prev = new;
			new->next = menvp->next;
			new->prev = menvp->prev;
			if (menvp->equal)
				new->equal = 1;
			free_t_envp(menvp);
			break ;
		}
		menvp = menvp->next;
	}
}

void	t_envp_update(t_envp **menvp, t_envp *new)
{
	if (!menvp || !new)
		return ;
	if (ft_strcmp((*menvp)->name, new->name) == 0)
	{
		new->next = (*menvp)->next;
		if ((*menvp)->next)
			(*menvp)->next->prev = new;
		if ((*menvp)->equal)
			new->equal = 1;
		free_t_envp(*menvp);
		*menvp = new;
		return ;
	}
	t_envp_update_2(*menvp, new);
}
