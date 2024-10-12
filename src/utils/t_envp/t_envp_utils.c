/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:24:05 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/11 17:53:09 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_envp_add_front(t_envp **menvp, t_envp *new)
{
	if (!menvp || !new)
		return ;
	if (!*menvp)
	{
		*menvp = new;
		return ;
	}
	if (t_envp_is_exist(*menvp, new->name))
	{
		t_envp_update(*menvp, new);
		return ;
	}
	new->next = *menvp;
	(*menvp)->prev = new;
	*menvp = new;
}

void	t_envp_add_back(t_envp **menvp, t_envp *new)
{
	t_envp	*tmp;

	if (!menvp || !new)
		return ;
	if (!*menvp)
	{
		*menvp = new;
		return ;
	}
	if (t_envp_is_exist(*menvp, new->name))
	{
		t_envp_update(*menvp, new);
		return ;
	}
	tmp = *menvp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_envp	*t_envp_new(char *name, char *value, int no_char_equal)
{
	t_envp	*new;
	int		i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_' && name[0] != '?'))
		return (NULL);
	i = -1;
	while (name[++i])
	{
		if (i == 0 && !isalnum(name[0]) && name[0] != '_' && name[0] != '?')
			return (NULL);
		else if (i != 0 && !isalnum(name[i]) && name[i] != '_')
			return (NULL);
	}
	new = ft_malloc(sizeof(t_envp));
	new->name = name;
	if (value)
		new->value = value;
	else
		new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->equal = !no_char_equal;
	return (new);
}

t_envp	*t_envp_init(char **envp)
{
	t_envp	*menvp;
	char	**tmp;
	int		i;

	menvp = NULL;
	i = -1;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp)
		{
			ft_free(tmp);
			break ;
		}
		if (str_ptr_size(tmp) == 1)
			t_envp_add_back(&menvp, t_envp_new(tmp[0], NULL,
					!ft_strchr(*envp, '=')));
		else
			t_envp_add_back(&menvp, t_envp_new(tmp[0],
					concat_str_equal_sign(tmp), !ft_strchr(envp[i], '=')));
		ft_free(tmp);
	}
	t_envp_init_2(&menvp, envp);
	return (menvp);
}

char	**t_envp_convert_to_str(t_envp *menvp)
{
	char	**ptr;
	char	*tmp;
	char	*buff;
	int		size;

	size = t_envp_size(menvp);
	ptr = ft_malloc((size + 1) * sizeof(char *));
	size = 0;
	while (menvp)
	{
		tmp = ft_strjoin(menvp->name, "=");
		if (menvp->value)
		{
			buff = tmp;
			tmp = ft_strjoin(tmp, menvp->value);
			ft_free(buff);
		}
		ptr[size++] = tmp;
		menvp = menvp->next;
	}
	ptr[size] = NULL;
	return (ptr);
}
