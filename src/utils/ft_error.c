/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:19:12 by Théo              #+#    #+#             */
/*   Updated: 2024/07/12 00:21:18 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	raise_perror(char *error, int critical)
{
	perror(error);
	if (critical == 1)
		exit(errno);
}

void	raise_error(char *error, char *details, int exit_code)
{
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
	exit(exit_code);
}	
