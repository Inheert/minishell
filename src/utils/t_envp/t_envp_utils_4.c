/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:00:04 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/11 11:19:48 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_envp_init_2(t_envp **menvp, char **envp)
{
	char	*tmp;

	t_envp_add_back(menvp, t_envp_new("?", "0", 0));
	if (str_ptr_size(envp))
		return ;
	tmp = getcwd(NULL, 0);
	t_envp_add_back(menvp, t_envp_new("PWD", ft_strdup(tmp), 0));
	t_envp_add_back(menvp, t_envp_new("SHLVL", "1", 0));
	t_envp_add_back(menvp, t_envp_new("_", "/usr/bin/env", 0));
	free(tmp);
}
