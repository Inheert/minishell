/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:09 by Théo              #+#    #+#             */
/*   Updated: 2024/09/14 18:19:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	status_code(char *code)
{
	int	result;

	result  = 0;
	while (*code)
	{
		if (*code < '0' || *code > '9')
			return (2);
		if ((size_t)result * 10 + (*code - '0') > LONG_MAX)
			return (2);
		result = result * 10 + (*code - '0');
		code++;
	}
	return (result % 256);
}

void	ft_exit(char **code)
{
	if (!code || str_ptr_size(code) <= 1)
	{
		ft_free_all();
		exit(0);
	}
	ft_free_all();
	exit(status_code(code[1]));
}
