/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:31 by Théo              #+#    #+#             */
/*   Updated: 2024/08/26 10:21:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var(char ***menvp, char *to_unset, int size)
{
	char	**new_menvp;
	char	**tmp;
	int		i;
	int		j;

	i = str_ptr_len(*menvp);
	new_menvp = ft_malloc(sizeof(char *) * (i + 1));
	new_menvp[i] = NULL;
	i = -1;
	j = 0;
	while ((*menvp)[++i])
	{
		tmp = ft_split((*menvp)[i], '=');
		if (tmp && ft_strncmp(tmp[0], to_unset, size) != 0)
			new_menvp[j++] = ft_strdup((*menvp)[i]);
		free_str_ptr(tmp);
	}
	free_str_ptr(*menvp);
	*menvp = new_menvp;
}

void	ft_unset(char ***menvp, char *to_unset)
{
	char	**tmp;
	int		size;
	int		i;

	if (!to_unset || !menvp || !*menvp)
		return ;
	size = ft_strlen(to_unset);
	i = -1;
	while ((*menvp)[++i])
	{
		tmp = ft_split((*menvp)[i], '=');
		if (tmp && ft_strncmp(tmp[0], to_unset, size) == 0)
		{
			unset_var(menvp, to_unset, size);
			break ;
		}
		free_str_ptr(tmp);
	}
}
