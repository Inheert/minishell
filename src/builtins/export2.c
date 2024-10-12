/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:54:42 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/11 10:57:56 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_new_var(char **cmd, char *equal, t_envp *menvp, int i)
{
	t_envp	*new;
	int		is_error;

	is_error = 0;
	new = t_envp_new(ft_substr(cmd[i], 0,
				ft_strlen(cmd[i]) - ft_strlen(equal)),
			ft_substr(equal + 1, 0, ft_strlen(equal) - 1), 0);
	if (!new || ft_strcmp(new->name, "?") == 0)
	{
		if (new)
			is_error = (free_t_envp(new), 1);
		ft_putstr_fd("export: '", 1);
		ft_putstr_fd(cmd[i], 1);
		raise_error("'", "not a valid identifier", 0, 1);
		return (is_error);
	}
	t_envp_add_back(&menvp, new);
	return (is_error);
}
