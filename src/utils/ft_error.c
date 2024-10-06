/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:55:48 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/06 18:40:08 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	raise_perror(char *error, int critical)
{
	perror(error);
	if (critical == 1)
	{
		ft_free_all();
		exit(errno);
	}
}

void	raise_error(char *error, char *details, int critical, int exit_code)
{
	if (error || details)
	{
		write(2, error, ft_strlen(error));
		write(2, ": ", 2);
		write(2, details, ft_strlen(details));
		write(2, "\n", 1);
	}
	if (critical == 1)
	{
		ft_free_all();
		exit(exit_code);
	}
}
