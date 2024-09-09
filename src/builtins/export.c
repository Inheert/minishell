/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:34 by Théo              #+#    #+#             */
/*   Updated: 2024/09/09 20:28:08 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
//
// EXPORT DOESN'T NOT REPLACE ENV VAR IF ALREADY EXIST BUT CREATE ANOTHER ONE
//
//

void	display_env_var(t_envp *menvp, t_envp *ignore)
{
	t_envp	*lowest;
	t_envp	*tmp;

	lowest = NULL;
	tmp = menvp;
	while (tmp)
	{
		if (!lowest || (ft_strcmp(lowest->name, tmp->name) > 0 && tmp != ignore))
		{
			printf("-- %s %s %s\n", tmp->name, lowest ? lowest->name : "null", ignore ? ignore->name : "null");
			lowest = tmp;
		}
		tmp = tmp->next;
	}
	printf("- %s\n", ignore ? ignore->name : "null");
	if (lowest != ignore)
	{
		printf("%s\n", lowest->name);
		display_env_var(menvp, lowest);
	}
}

char	*get_var(char **menvp, char *var)
{
	char	**tmp;
	char	**tmp2;
	size_t	size;

	tmp = ft_split(var, '=');
	if (!tmp)
		return (NULL);
	size = ft_strlen(tmp[0]);
	while (menvp)
	{
		tmp2 = ft_split(*menvp, '=');
		if (!tmp2)
			break ;
		if (tmp2 && ft_strcmp(tmp2[0], tmp[0]) == 0)
			return (free_str_ptr(tmp), free_str_ptr(tmp2), *menvp);
		free_str_ptr(tmp2);
		menvp++;
	}
	free_str_ptr(tmp);
	return (NULL);
}

void	ft_export(char **cmd, t_envp *menvp)
{
	if (!cmd || !menvp)
		return ;
	if (str_ptr_len(cmd) == 1)
		return (display_env_var(menvp, NULL));
	cmd = (char **)cmd;
	menvp = (t_envp *)menvp;
}
