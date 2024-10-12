/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:47 by Théo              #+#    #+#             */
/*   Updated: 2024/10/11 11:33:19 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Update the pwd and old_pwd env var update
static void	pwd_exist(t_envp *pwd, t_envp *old_pwd)
{
	char	*tmp;

	if (old_pwd)
	{
		ft_free(old_pwd->value);
		old_pwd->value = pwd->value;
	}
	else
		ft_free(pwd->value);
	tmp = getcwd(NULL, 0);
	pwd->value = ft_strdup(tmp);
	free(tmp);
}

// Update the old_pwd env var if pwd env var don't exist
static void	pwd_dont_exist(t_envp *menvp, t_envp *old_pwd)
{
	t_envp	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	pwd = t_envp_new("PWD", ft_strdup(tmp), 0);
	t_envp_add_back(&menvp, pwd);
	free(tmp);
	if (old_pwd && old_pwd->value)
	{
		ft_free(old_pwd->value);
		old_pwd->value = NULL;
		old_pwd->equal = 0;
	}
}

void	modify_envp_path(t_envp *menvp)
{
	t_envp	*pwd;
	t_envp	*old_pwd;

	pwd = t_envp_finding(menvp, "PWD");
	old_pwd = t_envp_finding(menvp, "OLDPWD");
	if (pwd)
		pwd_exist(pwd, old_pwd);
	else if (!pwd)
		pwd_dont_exist(menvp, old_pwd);
}

void	ft_cd(t_envp *menvp, char **cmd)
{
	char			*final_dir;
	t_envp			*home;
	DIR				*dir;
	unsigned int	i;

	home = t_envp_finding(menvp, "HOME");
	i = 1;
	final_dir = cmd[1];
	if (!cmd || !cmd[i])
	{
		if (!home)
			return (raise_error("cd: ", "HOME not set.", 0, 1));
		dir = opendir(home->value);
		final_dir = home->value;
	}
	else
		dir = opendir(cmd[1]);
	if (!dir)
		return (raise_perror(ft_strjoin(ft_strjoin(cmd[0], ": "), cmd[1]), 0));
	if (str_ptr_size(cmd) > 2)
		return (raise_error("cd", "too many arguments", 0, 1));
	chdir(final_dir);
	closedir(dir);
	modify_envp_path(menvp);
	set_exit_status(0, NULL);
}
