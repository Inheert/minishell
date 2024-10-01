/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:34 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/01 15:46:23 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*t_envp_finding(t_envp *menvp, char *name)
{
	if (!menvp || !name)
		return (NULL);
	while (menvp)
	{
		if (strcmp(menvp->name, name) == 0)
			return (menvp);
		menvp = menvp->next;
	}
	return (NULL);
}

static int	find_last_slash(char *path)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (path[++i])
		if (path[i] == '/')
			j = i;
	return (j);
}

static	void	set_pwd(t_envp *menvp, char *path)
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
		pwd->value = path;
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

void	t_envp_check(t_envp *menvp)
{
	DIR		*dir;
	t_envp	*env_var;
	char	*pwd;
	char	*tmp;
	int		idx;

	if (!menvp)
		return ;
	env_var = t_envp_finding(menvp, "PWD");
	if (!env_var)
		return ;
	pwd = ft_strdup(env_var->value);
	while (pwd)
	{
		dir = opendir(pwd);
		if (!dir)
		{
			idx = find_last_slash(pwd);
			if (idx == -1 || idx == 0)
				break ;
			tmp = pwd;
			pwd = ft_substr(pwd, 0, idx);
			ft_free(tmp);
		}
		else
			return (chdir(pwd), closedir(dir), set_pwd(menvp, pwd));
	}
}
