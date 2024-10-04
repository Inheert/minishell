/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 07:34:17 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/04 16:28:18 by tclaereb         ###   ########.fr       */
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
			return (NULL);
		full_path = ft_strjoin(partial_path, cmd[0]);
		if (!full_path)
			return (free(partial_path), NULL);
		ft_free(partial_path);
		if (access(full_path, X_OK) == 0 || access(full_path, F_OK) == 0)
			return (full_path);
		ft_free(full_path);
	}
	return (NULL);
}

char	*find_path(char **cmd, char **envp)
{
	if (ft_strlen(cmd[0]) == 0)
		return (raise_error("Command not valid",
				"command len is equal to 0", 1, 1), NULL);
	if (is_command_builtin(cmd[0]))
		return (cmd[0]);
	if (!envp || !*envp)
		return (raise_error("envp error", "envp is missing or NULL", 1, 1),
			NULL);
	if (access(cmd[0], X_OK) == 0 && ft_strncmp(cmd[0], "./", 2) == 0)
		return (printf("XOK\n"), cmd[0]);
	else if (access(cmd[0], F_OK) == 0 && ft_strncmp(cmd[0], "./", 2) == 0)
		return (printf("FOK\n"), cmd[0]);
	else if (ft_strncmp(cmd[0], "./", 2) == 0)
		return (NULL);
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
