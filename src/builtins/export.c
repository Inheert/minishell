/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:34 by Théo              #+#    #+#             */
/*   Updated: 2024/10/06 13:17:39 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
//
// EXPORT DOESN'T NOT REPLACE ENV VAR IF ALREADY EXIST BUT CREATE ANOTHER ONE
//
//

void	prepare_display_2(int menvp_size, char **var_name)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < menvp_size)
	{
		j = -1;
		while (++j < menvp_size - 1)
		{
			if (ft_strcmp(var_name[j], var_name[j + 1]) > 0)
			{
				tmp = var_name[j];
				var_name[j] = var_name[j + 1];
				var_name[j + 1] = tmp;
			}
		}
	}
}

char	**prepare_display(t_envp *menvp, t_envp *tmp_menvp)
{
	char	**var_name;
	int		menvp_size;
	int		i;

	tmp_menvp = menvp;
	menvp_size = t_envp_size(menvp);
	var_name = ft_malloc(sizeof(char *) * (menvp_size + 1));
	i = -1;
	while (tmp_menvp)
	{
		var_name[++i] = ft_strdup(tmp_menvp->name);
		tmp_menvp = tmp_menvp->next;
	}
	var_name[i + 1] = NULL;
	i = -1;
	prepare_display_2(menvp_size, var_name);
	return (var_name);
}

void	display_env_var(char *var_name, t_processus *process, t_envp *tmp_menvp)
{
	while (tmp_menvp)
	{
		if (ft_strcmp(var_name, tmp_menvp->name) == 0)
		{
			ft_putstr_fd("declare -x ", get_fds(process, STDOUT_FILENO));
			ft_putstr_fd(tmp_menvp->name, get_fds(process, STDOUT_FILENO));
			if (tmp_menvp->equal && !tmp_menvp->value)
				ft_putendl_fd("=\"\"\n", get_fds(process, STDOUT_FILENO));
			else if (!tmp_menvp->equal && !tmp_menvp->value)
				ft_putstr_fd("\n", get_fds(process, STDOUT_FILENO));
			else
			{
				ft_putstr_fd(tmp_menvp->value, get_fds(process, STDOUT_FILENO));
				ft_putendl_fd(tmp_menvp->value,
					get_fds(process, STDOUT_FILENO));
			}
			break ;
		}
		tmp_menvp = tmp_menvp->next;
	}
}

void	set_var(t_envp *menvp, char **cmd)
{
	char	**new_var;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		new_var = ft_split(cmd[i], '=');
		if (!new_var)
		{
			ft_free(new_var);
			continue ;
		}
		if (str_ptr_size(new_var) == 1)
			t_envp_add_back(&menvp, t_envp_new(new_var[0], NULL,
					!ft_strchr(cmd[i], '=')));
		else
			t_envp_add_back(&menvp, t_envp_new(new_var[0],
					concat_str_equal_sign(new_var),
					!ft_strchr(cmd[i], '=')));
		free_str_ptr(new_var);
	}
}

void	ft_export(char **cmd, t_processus *process, t_envp *menvp)
{
	char	**var_name;
	t_envp	*tmp_menvp;
	int		i;

	if (!cmd || !menvp)
		return ;
	if (str_ptr_size(cmd) == 1)
	{
		tmp_menvp = NULL;
		var_name = prepare_display(menvp, tmp_menvp);
		i = -1;
		while (var_name[++i])
		{
			tmp_menvp = menvp;
			display_env_var(var_name[i], process, tmp_menvp);
			tmp_menvp = tmp_menvp->next;
		}
		free_str_ptr(var_name);
	}
	else
		return (set_var(menvp, cmd));
}
