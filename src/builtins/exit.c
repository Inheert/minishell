/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:09 by Théo              #+#    #+#             */
/*   Updated: 2024/09/14 20:42:22 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	status_code(char *code)
{
	int	result;

	result  = 0;
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

void	ft_exit(char **code)
{
	int	exit_code;

	if (!code || str_ptr_size(code) <= 1)
	{
		ft_free_all();
		exit(0);
	}
	else if (str_ptr_size(code) != 2)
	{
		raise_error("exit", "too many arguments", 0, 1);
		return ;
	}
	exit_code = status_code(code[1]);
	ft_free_all();
	exit(exit_code);
}
