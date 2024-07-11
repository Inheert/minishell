/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:23 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 01:28:23 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void *ptr, size_t size)
{
	if (!ptr)
		return ;
	ft_bzero(ptr, size);
	free(ptr);
}

void	free_str_ptr(char **ptr)
{
	size_t	i;
	size_t	size;

	if (!ptr || !*ptr)
		return ;
	i = -1;
	size = str_ptr_len(ptr);
	while (++i < size && ptr[i])
		ft_free(ptr[i], ft_strlen(ptr[i]));
	ft_free(ptr, str_ptr_len(ptr));
}

void	free_t_command(t_command **commands)
{
	size_t	i;
	size_t	size;

	if (!commands || !*commands)
		return ;
	i = 0;
	size = t_command_len(commands);
	while (i < size && commands[i])
	{
		printf("here4\n");
		if (commands[i]->options && commands[i]->options[0] != commands[i]->command)
			ft_free((commands[i]->command), ft_strlen(commands[i]->command));
		printf("here4\n");
		if (commands[i]->options)
			free_str_ptr(commands[i]->options);
		ft_free(commands[i]->fd, fd_ptr_len(commands[i]->fd));
		ft_free(commands[i], 1);
		i++;
	}
	ft_free(commands, size);
}
