/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:27 by Théo              #+#    #+#             */
/*   Updated: 2024/08/22 01:29:38 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	unsigned int	size;

	if (!cmd)
		return ;
	size = str_ptr_len(cmd);
	if (size == 1)
		printf("\n");
	// if (size > 1)
	// {
	// 	while (*cmd)
	// 	{
	// 		*cmd++;
	// 	}
	// }
	printf("echo");
	ft_free_all();
	exit(EXIT_SUCCESS);
}