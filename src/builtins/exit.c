/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:09 by Théo              #+#    #+#             */
/*   Updated: 2024/10/05 17:55:52 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	status_code(char *code)
{
	int	result;

	result = 0;
	if (*code == '+' || *code == '-')
		code++;
	if (!code)
		return (2);
	while (*code)
	{
		if (*code < '0' || *code > '9')
			return (2);
		if ((size_t)result * 10 + (*code - '0') > LONG_MAX)
			return (2);
		result = result * 10 + (*code - '0');
		code++;
	}
	return (result);
}

void	ft_exit(t_processus *pipes, char **code)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	if (!code || str_ptr_size(code) <= 1)
	{
		t_processus_close_builtin_fds(pipes);
		ft_free_all();
		exit(0);
	}
	else if (str_ptr_size(code) != 2)
	{
		raise_error("exit", "too many arguments", 0, 1);
		return ;
	}
	t_processus_close_builtin_fds(pipes);
	exit_code = status_code(code[1]);
	ft_free_all();
	exit(exit_code);
}
