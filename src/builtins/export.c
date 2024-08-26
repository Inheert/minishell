/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:34 by Théo              #+#    #+#             */
/*   Updated: 2024/08/26 14:15:57 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (++j < size- 1)
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
		write(1, "\n", 1);
	}
}

void	ft_export(char **cmd, char ***menvp)
{
	if (!cmd || !menvp || !*menvp)
		return ;
	if (str_ptr_len(cmd) == 1)
		return (display_env_var(*menvp));
	cmd = (char **)cmd;
	menvp = (char ***)menvp;
}
