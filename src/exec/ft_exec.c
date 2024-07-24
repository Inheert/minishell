/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/24 10:35:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*prepare_pipes(t_token **tokens)
{
	t_pipe	*pipes;
	t_pipe	*tmp_pipe;
	t_token	*tmp_token;

	pipes = NULL;
	tmp_pipe = NULL;
	tmp_token = *tokens;
	while (tmp_token)
	{
		if (!tmp_pipe)
			tmp_pipe = ft_pipe_new();
		if (tmp_token->token != PIPE)
			ft_token_add_back(&tmp_pipe->tokens, ft_token_copy(tmp_token));
		else
		{
			ft_pipe_add_back(&pipes, tmp_pipe);
			tmp_pipe = NULL;
		}
		tmp_token = tmp_token->next;
	}
	if (tmp_pipe)
		ft_pipe_add_back(&pipes, tmp_pipe);
	free_t_token(*tokens);
	*tokens = NULL;
	return (pipes);
}

void	token_management(t_pipe *pipes, t_token *token)
{
	int		fd;

	while (token)
	{
		if (token->token == REDIR_IN)
		{
			fd = open(token->str, O_RDONLY);
			if (fd == -1)
				return (ft_pipe_close_fds(pipes),
					raise_perror("File open failed", 1));
			if (dup2(fd, pipes->fds[0]) == -1)
				return (ft_pipe_close_fds(pipes),
					raise_perror("dup2 failed", 1));
			pipes->fds[0] = fd;
		}
		else if (token->token == REDIR_OUT)
		{
			fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (ft_pipe_close_fds(pipes),
						raise_perror("File open failed", 1));
			if (dup2(fd, pipes->fds[1]) == -1)
				return (ft_pipe_close_fds(pipes),
						raise_perror("dup2 failed", 1));
			pipes->fds[1] = fd;
		}
		token = token->next;
	}
}

void	exec_main_processus(t_pipe *pipe)
{
	t_token	*tmp;

	tmp = pipe->tokens;
	while (tmp)
	{
		token_management(pipe, tmp);
		tmp = tmp->next;
	}
}

void	exec_first_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	fprintf(stderr, "test\n");
	if (dup2(pipes->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	token_management(pipes, pipes->tokens);
	ft_pipe_close_fds(pipes);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_first_processus", 1));
	cmd = ft_split(token->str, ' ');
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_first_processus", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error("Command not found", "func: exec_first_processus", 1));
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

void	exec_middle_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	if (dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	token_management(pipes, pipes->tokens);
	ft_pipe_close_fds(pipes);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_middle_processus", 1));
	cmd = ft_split(token->str, ' ');
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_middle_processus", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error("Command not found", "func. exec_middle_processus", 1));
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

void	exec_last_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	if (pipes->prev && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	token_management(pipes, pipes->tokens);
	ft_pipe_close_fds(pipes);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_last_processus", 1));
	cmd = ft_split(token->str, ' ');
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_last_processus", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error("Command not found", "func. exec_last_processus", 1));
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

// First sub process write output in the standard output even if an outfile is given
// Last processus dont write output at all
void	exec_sub_processus(t_pipe *pipes, unsigned int size, unsigned int i, char **envp)
{
	if (i == size)
		exec_last_processus(pipes, envp);
	else if (i == 1)
		exec_first_processus(pipes, envp);
	else
		exec_middle_processus(pipes, envp);
	while (pipes)
	{
		if (waitpid(pipes->pid, NULL, 0) == -1)
			raise_perror("waitpid failed", 1);
		pipes = pipes->next;
	}
}

void	ft_exec(t_token **tokens, char **envp)
{
	t_pipe			*pipes;
	unsigned int	size;
	unsigned int	i;

	pipes = prepare_pipes(tokens);
	if (!pipes)
		return ;
	size = pipe_ptr_size(pipes);
	i = 1;
	while (pipes)
	{
		if (size != 1)
		{
			if (pipe(pipes->fds) == -1)
				raise_perror("Pipe creation failed", 1);
		}
		pipes->pid = fork();
		if (pipes->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (pipes->pid == 0)
			exec_sub_processus(pipes, size, i, envp);
		i++;
		pipes = pipes->next;
	}
	// if (pipe_ptr_size(pipes) == 1)
	// 	exec_main_processus(pipes);
}
