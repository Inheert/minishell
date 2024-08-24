/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/08/24 16:08:40 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Why heredoc dont work good when he is part of a middle processus? What pipe create this problem? What connection/dup2 is wrong/missing?
// Is all fds are closed in the right way? Even for errors?

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
	t_token	*tmp;
	char	*buff;
	int		fdin;
	int		fdout;

	fdin = -1;
	fdout = -1;
	while (token)
	{
		tmp = NULL;
		buff = NULL;
		if (token->token == HERE_DOC)
		{
			if (pipes->here_doc[0] == -1 && pipes->here_doc[1] == -1)
				if (pipe(pipes->here_doc) == -1)
					raise_perror("Here_doc buffer creation failed (pipe)", 1);
			while (1)
			{
				buff = readline("> ");
				if (buff && ft_strncmp(buff, token->str, ft_strlen(token->str)) == 0)
					break ;
				write(pipes->here_doc[1], buff, ft_strlen(buff));
				write(pipes->here_doc[1], "\n", 1);
			}
			if (dup2(pipes->here_doc[0], 0) == -1)
				return (ft_pipe_close_fds(pipes), raise_perror("dup2 failed", 1));
			tmp = token;
		}
		else if (token->token == REDIR_IN)
		{
			fdin = open(token->str, O_RDONLY);
			if (fdin == -1)
				return (ft_pipe_close_fds(pipes),
					raise_perror(token->str, 1));
			tmp = token;
		}
		else if (token->token == REDIR_OUT)
		{
			fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fdout == -1)
				return (ft_pipe_close_fds(pipes),
					raise_perror(token->str, 1));
			tmp = token;
		}
		token = token->next;
		ft_token_del(&pipes->tokens, tmp);
	}
	if (fdin != -1)
	{
		if (dup2(fdin, 0) == -1)
			return (ft_pipe_close_fds(pipes),
					raise_perror("dup2 failed", 1));
		pipes->fds[0] = fdin;
	}
	if (fdout != -1)
	{
		if (dup2(fdout, 1) == -1)
			return (ft_pipe_close_fds(pipes),
					raise_perror("dup2 failed", 1));
		pipes->fds[1] = fdout;
	}
}

void	exec_first_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	token_management(pipes, pipes->tokens);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	ft_pipe_close_fds(pipes);
	if (pipes->here_doc[0] != -1)
		close(pipes->here_doc[0]);
	if (pipes->here_doc[1] != -1)
		close(pipes->here_doc[1]);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_first_processus", 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_first_processus", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

void	exec_middle_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	token_management(pipes, pipes->tokens);
	if (pipes->here_doc[0] == -1 && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	if (dup2(pipes->fds[1], 1) == -1)
		raise_perror("dup2 failed", 1);
	ft_pipe_close_fds(pipes);
	ft_pipe_close_fds(pipes->prev);
	if (pipes->here_doc[0] != -1)
		close(pipes->here_doc[0]);
	if (pipes->here_doc[1] != -1)
		close(pipes->here_doc[1]);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_middle_processus", 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_middle_processus", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		raise_perror("execve error", 1);
}

void	exec_last_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	token_management(pipes, pipes->tokens);
	if (pipes->prev && dup2(pipes->prev->fds[0], 0) == -1)
		raise_perror("dup2 failed", 1);
	ft_pipe_close_fds(pipes->prev);
	if (pipes->here_doc[0] != -1)
		close(pipes->here_doc[0]);
	if (pipes->here_doc[1] != -1)
		close(pipes->here_doc[1]);
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_last_processus", 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_last_processus", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (raise_error(cmd[0], "command not found", 1));
	if (is_command_builtin(cmd_path))
		exec_builtins(cmd);
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
}

void	exec_main_processus(t_pipe *pipes, char **envp)
{
	t_token	*token;
	char	**cmd;

	envp = (char **)envp;
	token = ft_find_token(pipes, COMMAND);
	if (!token)
		return (raise_error("COMMAND token not found", "func: exec_last_processus", 1));
	cmd = token_struct_to_str_ptr(token);
	if (!cmd)
		return (raise_error("Cmd split returned NULL", "func: exec_last_processus", 1));
	exec_builtins(cmd);
}

void	ft_exec(t_token **tokens, char **envp)
{
	t_pipe			*pipes;
	t_pipe			*tmp;
	unsigned int	size;
	unsigned int	i;

	pipes = prepare_pipes(tokens);
	if (!pipes)
		return ;
	tmp = pipes;
	size = pipe_ptr_size(pipes);
	i = 1;
	if (size == 1 && ft_find_token(pipes, COMMAND) && is_command_builtin(ft_find_token(pipes, COMMAND)->str))
		return (exec_main_processus(pipes, envp));
	while (pipes)
	{
		pipes->pid = fork();
		if (pipes->pid == -1)
			raise_perror("Fork creation failed", 1);
		if (pipes->pid == 0)
			exec_sub_processus(pipes, size, i, envp);
		i++;
		if (pipes->prev)
			ft_pipe_close_fds(pipes->prev);
		pipes = pipes->next;
	}
	while (tmp)
	{
		if (waitpid(tmp->pid, NULL, 0) == -1)
			raise_perror("waitpid failed", 1);
		tmp = tmp->next;
	}
}
