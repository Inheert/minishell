/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:37:42 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/11 17:50:01 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_envp_display(t_envp *menvp)
{
	while (menvp)
	{
		printf("NAME: %s\nVALUE: %s\n\n", menvp->name, menvp->value);
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

void	t_envp_update(t_envp *menvp, t_envp *new)
{
	if (!menvp || !new)
		return ;
	while (menvp)
	{
		if (ft_strcmp(menvp->name, new->name) == 0)
		{
			ft_free(menvp->value);
			menvp->value = ft_strdup(new->value);
			free_t_envp(new);
			break ;
		}
		menvp = menvp->next;
	}
}
