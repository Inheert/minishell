/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:24:05 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/08 16:02:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_envp_display(t_envp *envp)
{
	while (envp)
	{
		fprintf(stderr, "NAME: %s VALUE: %s\n", envp->name, envp->value);
		envp = envp->next;
	}
}

void	t_envp_add_front(t_envp **envp, t_envp *new)
{
	if (!envp || !new)
		return ;
	if (!*envp)
	{
		*envp = new;
		return ;
	}
	new->next = *envp;
	(*envp)->prev = new;
	*envp = new;
}

void	t_envp_add_back(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!envp || !new)
		return ;
	if (!*envp)
	{
		*envp = new;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_envp	*t_envp_new(char *name, char *value)
{
	t_envp	*new;

	if (!name)
		return (NULL);
	new = ft_malloc(sizeof(t_envp));
	new->name = name;
	if (value)
		new->value = value;
	else
		new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static char	*concat_str(char **str)
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

t_envp	*init_envp(char **envp)
{
	t_envp	*menvp;
	char	**tmp;

	if (!envp)
		return (NULL);
	menvp = NULL;
	while (envp)
	{
		tmp = ft_split(*envp, '=');
		if (!tmp)
		{
			ft_free(tmp);
			break ;
		}
		if (str_ptr_len(tmp) == 1)
			t_envp_add_back(&menvp, t_envp_new(tmp[0], NULL));
		else
			t_envp_add_back(&menvp, t_envp_new(tmp[0], concat_str(tmp)));
		ft_free(tmp);
		envp++;
	}
	return (menvp);
}

char	**create_str_envp(t_envp *menvp)
{
	char	**ptr;
	char	*tmp;
	char	*buff;
	int		size;

	size = menvp_ptr_size(menvp);
	ptr = ft_malloc((size + 1) * sizeof(char));
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
