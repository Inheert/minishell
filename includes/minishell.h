/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:28:35 by Théo              #+#    #+#             */
/*   Updated: 2024/07/11 01:28:35 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/utils/libft/libft.h"

# define PIPE 0
# define SEMICOLON 1
# define REDIR_APPEND 2
# define REDIR_IN 3
# define REDIR_OUT 4

typedef struct s_command
{
	char	*command;
	char	**options;
	char	**envp;
	int		(*fd)[2];
}	t_command;

typedef struct s_token
{
	char		*str;
	int			token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

unsigned int	str_ptr_len(char **ptr);
unsigned int	t_command_len(t_command **commands);
unsigned int	fd_ptr_len(int (*fd)[2]);
unsigned int	count_infile(char *s);

void		free_str_ptr(char **ptr);
void		free_t_command(t_command **commands);

char		**copy_str_ptr(char **ptr);

t_command	**create_commands_struct(int argc, char **argv, char **envp);

#endif