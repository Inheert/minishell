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
# define STRING 1 //'$HOME' == string $HOME
# define REDIR_APPEND_OUT 2
# define HERE_DOC 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define COMMAND 6
# define ENV 7 //$HOME
# define EXIT_STATUS 8 //$?


typedef struct s_token
{
	char		*str;
	int			token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Tokenisation
t_token			*tokenization(char *argv);

// Utils - ptr size functions
unsigned int	token_ptr_size(t_token *token);
unsigned int	str_ptr_len(char **ptr);
unsigned int	fd_ptr_len(int (*fd)[2]);
unsigned int	count_infile(char *s);

// Utils - malloc free functions
void			free_t_token(t_token **token);
void			free_str_ptr(char **ptr);

// Utils - token structure manipulation
void			ft_token_add_front(t_token **token, t_token *new);
void			ft_token_add_back(t_token **token, t_token *new);
t_token			*ft_token_new(char *str, int token);

// Utils - other
char			**copy_str_ptr(char **ptr);

// Exec
int				execute_commands(t_token *token);

#endif