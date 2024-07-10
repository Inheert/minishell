/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:50:11 by marvin            #+#    #+#             */
/*   Updated: 2024/07/11 00:50:11 by marvin           ###   ########.fr       */
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

typedef struct s_command
{
	char	*command;
	char	**options;
	char	**envp;
	int		(*fd)[2];
}	t_command;

size_t		str_ptr_len(char **ptr);
size_t		t_command_len(t_command **commands);

void		free_str_ptr(char **ptr);
void		free_t_command(t_command **commands);

t_command	**create_commands_struct(int argc, char **argv, char **envp);


#endif