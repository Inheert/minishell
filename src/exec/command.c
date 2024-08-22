/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 07:34:17 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/21 22:53:12 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char **cmd, char **envp)
{
	int		i;
	char	*partial_path;
	char	*full_path;

	i = -1;
	while (envp[++i])
	{
		partial_path = ft_strjoin(envp[i], "/");
		if (!partial_path)
			return (free_str_ptr(envp), NULL);
		full_path = ft_strjoin(partial_path, cmd[0]);
		if (!full_path)
			return (free(partial_path), free_str_ptr(envp), NULL);
		free(partial_path);
		if (access(full_path, X_OK) == 0 || access(full_path, F_OK) == 0)
			return (free_str_ptr(envp), full_path);
		free(full_path);
	}
	free_str_ptr(envp);
	return (NULL);
}

char	*find_path(char **cmd, char **envp)
{
	if (ft_strlen(cmd[0]) == 0)
		return (free_str_ptr(cmd), raise_error("Command not valid",
				"command len is equal to 0", 1), NULL);
	if (is_command_builtin(cmd[0]))
		return (cmd[0]);
	if (!envp || !*envp)
		return (free_str_ptr(cmd),
			raise_error("envp error", "envp is missing or NULL", 1), NULL);
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	else if (access(cmd[0], F_OK) == 0 && cmd[0][0] == '.')
		return (free_str_ptr(cmd), raise_error("Permission denied",
				"command can be executed", 126), NULL);
	while (envp && *envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envp = ft_split(*envp, ':');
	if (!envp)
		return (NULL);
	*envp = ft_substr(*envp, 5, ft_strlen(*envp));
	if (!envp)
		return (NULL);
	return (check_path(cmd, envp));
}
