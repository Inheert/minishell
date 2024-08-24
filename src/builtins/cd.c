/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:47 by Théo              #+#    #+#             */
/*   Updated: 2024/08/24 16:21:31 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmd)
{
	DIR				*dir;
	unsigned int	i;

	i = 1;
	if (!cmd[i])
		return ;
	if (str_ptr_len(cmd) > 2)
		raise_error("cd", "too many arguments", 0, 1);
	dir = opendir(cmd[1]);
	if (dir)
	{
		chdir(cmd[1]);
		closedir(dir);
	}
	else
		raise_perror(cmd[0], 0);
}
