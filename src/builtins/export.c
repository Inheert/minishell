/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:34 by Théo              #+#    #+#             */
/*   Updated: 2024/08/28 16:54:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
//
// EXPORT DOESN'T NOT REPLACE ENV VAR IF ALREADY EXIST BUT CREATE ANOTHER ONE
//
//

void	display_env_var(char **menvp)
{
	char	**tmp;
	char	*buff;
	int		size;
	int		i;
	int		j;

	tmp = copy_str_ptr(menvp);
	size = str_ptr_len(tmp);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1)
		{
			if (ft_strncmp(tmp[j], tmp[j + 1], ft_strlen(tmp[j])) > 0)
			{
				buff = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = buff;
			}
		}
	}
	i = -1;
	while (tmp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp[i], 1);
		if (ft_strchr(tmp[i], '=') == tmp[i] + ft_strlen(tmp[i]) - 1)
			write(1, "\"\"", 2);
		write(1, "\n", 1);
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
		if (tmp2 && ft_strncmp(tmp2[0], tmp[0], size) == 0 && size == ft_strlen(tmp2[0]))
			return (free_str_ptr(tmp), free_str_ptr(tmp2), *menvp);
		free_str_ptr(tmp2);
		menvp++;
	}
	free_str_ptr(tmp);
	return (NULL);
}

void	create_var(char **cmd, char ***menvp)
{
	char	**new_var;
	char	*tmp;
	int		size;
	int		i;
	int		j;

	size = str_ptr_len(cmd);
	new_var = ft_malloc((size + str_ptr_len(*menvp)) * sizeof(char *));
	new_var[size - 1] = NULL;
	i = -1;
	while ((*menvp)[++i])
		new_var[i] = ft_strdup((*menvp)[i]);
	j = 0;
	while (cmd[++j])
	{
		tmp = get_var(new_var, cmd[j]);
		if (tmp)
			new_var[i] = ft_strdup((ft_free(new_var[i]), cmd[j]));
		else
			new_var[i] = ft_strdup(cmd[j]);
		i++;
	}
	free_str_ptr(*menvp);
	*menvp = new_var;
}

void	ft_export(char **cmd, char ***menvp)
{
	if (!cmd || !menvp || !*menvp)
		return ;
	if (str_ptr_len(cmd) == 1)
		return (display_env_var(*menvp));
	else if (str_ptr_len(cmd) > 1)
		return (create_var(cmd, menvp));
	cmd = (char **)cmd;
	menvp = (char ***)menvp;
}
