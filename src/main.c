/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:05 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 01:28:05 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		**ft_envp;
	t_command	**commands;

	ft_envp = copy_str_ptr(envp);
	commands = create_commands_struct(argc, argv, envp);
	free_t_command(commands);
	free_str_ptr(ft_envp);
	return (0);
}
