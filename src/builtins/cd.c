/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:47 by Théo              #+#    #+#             */
/*   Updated: 2024/09/10 18:12:36 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_envp_path(t_envp *menvp)
{
	t_envp	*pwd;
	t_envp	*old_pwd;

	pwd = t_envp_finding(menvp, "PWD");
	old_pwd = t_envp_finding(menvp, "OLDPWD");
	if (pwd)
	{
		if (old_pwd)
		{
			ft_free(old_pwd->value);
			old_pwd->value = pwd->value;
		}
		else
			ft_free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
	else if (!pwd)
	{
		if (old_pwd && old_pwd->value)
		{
			ft_free(old_pwd->value);
			old_pwd->value = NULL;
			old_pwd->equal = 0;
		}
	}
}

void	ft_cd(t_envp *menvp, char **cmd)
{
	DIR				*dir;
	unsigned int	i;

	i = 1;
	if (!cmd[i])
		return ;
	dir = opendir(cmd[1]);
	if (!dir)
		return (raise_perror(ft_strjoin(ft_strjoin(cmd[0], ": "), cmd[1]), 0));
	if (str_ptr_size(cmd) > 2)
		return (raise_error("cd", "too many arguments", 0, 1));
	chdir(cmd[1]);
	closedir(dir);
	modify_envp_path(menvp);
}
