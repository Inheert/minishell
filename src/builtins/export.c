/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:34 by Théo              #+#    #+#             */
/*   Updated: 2024/10/11 17:50:44 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_display_2(int menvp_size, char **var_name)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < menvp_size)
	{
		j = -1;
		while (++j < menvp_size - 2)
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

static char	**prepare_display(t_envp *menvp, t_envp *tmp_menvp)
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
		if (ft_strcmp(tmp_menvp->name, "?") != 0)
			var_name[++i] = ft_strdup(tmp_menvp->name);
		tmp_menvp = tmp_menvp->next;
	}
	var_name[i + 1] = NULL;
	i = -1;
	prepare_display_2(menvp_size, var_name);
	return (var_name);
}

static void	display_env_var(char *var_name, t_processus *process,
	t_envp *tmp_menvp)
{
	while (tmp_menvp)
	{
		if (ft_strcmp(var_name, tmp_menvp->name) == 0
			&& ft_strcmp(tmp_menvp->name, "_") != 0)
		{
			ft_putstr_fd("declare -x ", get_fds(process, STDOUT_FILENO));
			ft_putstr_fd(tmp_menvp->name, get_fds(process, STDOUT_FILENO));
			if (tmp_menvp->equal && !tmp_menvp->value)
				ft_putendl_fd("=\"\"\n", get_fds(process, STDOUT_FILENO));
			else if (!tmp_menvp->equal && !tmp_menvp->value)
				ft_putstr_fd("\n", get_fds(process, STDOUT_FILENO));
			else
			{
				ft_putstr_fd("=", get_fds(process, STDOUT_FILENO));
				ft_putendl_fd(tmp_menvp->value,
					get_fds(process, STDOUT_FILENO));
			}
			break ;
		}
		tmp_menvp = tmp_menvp->next;
	}
}

static int	set_var(t_envp *menvp, char **cmd)
{
	char	*equal;
	int		is_error;
	int		i;

	is_error = 0;
	i = 0;
	while (cmd[++i])
	{
		equal = ft_strchr(cmd[i], '=');
		if (equal)
			is_error = manage_new_var(cmd, equal, menvp, i);
	}
	return (is_error);
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
		set_exit_status(0, NULL);
	}
	else
	{
		if (!set_var(menvp, cmd))
			set_exit_status(0, NULL);
	}
}
