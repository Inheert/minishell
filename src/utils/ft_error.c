/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:48 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/11 19:40:14 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int code, t_envp **menvp)
{
	static t_envp	**_menvp = NULL;
	t_envp			*exit_status_var;

	if (menvp && !_menvp)
	{
		_menvp = menvp;
		return ;
	}
	if (!_menvp)
		return ;
	exit_status_var = t_envp_finding(*_menvp, "?");
	if (!exit_status_var)
		return ;
	ft_free(exit_status_var->value);
	exit_status_var->value = ft_itoa(code);
}

void	raise_perror(char *error, int critical)
{
	perror(error);
	set_exit_status(errno, NULL);
	if (critical == 1)
	{
		ft_free_all();
		exit(errno);
	}
}

void	raise_error(char *error, char *details, int critical, int exit_code)
{
	set_exit_status(exit_code, NULL);
	if (error)
	{
		if (ft_strlen(error) > 0)
			write(2, error, ft_strlen(error));
		else
			write(2, "''", 2);
	}
	if (details)
	{
		write(2, ": ", 2);
		write(2, details, ft_strlen(details));
	}
	if (error || details)
		write(2, "\n", 1);
	if (critical == 1)
	{
		ft_free_all();
		exit(exit_code);
	}
}
