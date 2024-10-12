/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:09 by Théo              #+#    #+#             */
/*   Updated: 2024/10/09 18:00:26 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adapted version of atoi to return the exit code.
static long long	status_code(char *code)
{
	long long	result;
	long long	neg;

	neg = 1;
	result = 0;
	if (*code == '+')
		code++;
	else if (*code == '-' )
		neg = (code++, -1);
	if (!code)
		return (2);
	while (*code)
	{
		if (*code < '0' || *code > '9')
			return (-1);
		if ((size_t)result * 10 + (*code - '0') > LONG_LONG_MAX)
			return (-1);
		result = result * 10 + (*code - '0');
		code++;
	}
	if (result * neg < LONG_LONG_MIN)
		return (-1);
	return (result * neg);
}

void	ft_exit(t_processus *process, char **code)
{
	long long	exit_code;

	ft_putendl_fd("exit", 1);
	if (!code || str_ptr_size(code) <= 1)
	{
		exit_code = ft_atoi(t_envp_finding(*process->menvp, "?")->value);
		t_processus_close_builtin_fds(process);
		ft_free_all();
		exit(exit_code);
	}
	exit_code = status_code(code[1]);
	if ((exit_code == -1 && ft_strcmp(code[1], "-1") != 0))
	{
		raise_error("exit: ",
			ft_strjoin(code[1], ": numeric argument required"), 1, 2);
	}
	else if (str_ptr_size(code) > 2)
	{
		raise_error("exit", "too many arguments", 0, 1);
		return ;
	}
	t_processus_close_builtin_fds(process);
	ft_free_all();
	exit(exit_code);
}
