/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:05:38 by Théo              #+#    #+#             */
/*   Updated: 2024/10/05 17:55:52 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_processus *pipes)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, get_fds(pipes, STDOUT_FILENO));
	free(cwd);
}
