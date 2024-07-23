/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:56:47 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:56:47 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/utils/libft/libft.h"
# include "../src/utils/garbage_collector/includes/garbage_collector.h"

# define malloc ft_malloc
# define free ft_free

# define PIPE 1
# define STRING 2 //'$HOME' == string $HOME
# define REDIR_APPEND_OUT 3
# define HERE_DOC 4
# define REDIR_IN 5
# define REDIR_OUT 6
# define COMMAND 7
# define ENV 8 //HOME
# define EXIT_STATUS 9 //$?

typedef struct s_token
{
	char		*str;
	int			token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_pipe
{
	struct s_token *tokens;
	int				fds[2];
	struct s_pipe	*next;
	struct s_pipe	*prev;
}	t_pipe;

t_token			*tokenization(char *prompt);

// Utils - Error management
void			raise_perror(char *error, int critical);
void			raise_error(char *error, char *details, int exit_code);

// Utils - Ptr size functions
unsigned int	token_ptr_size(t_token *token);
unsigned int	pipe_ptr_size(t_pipe *pipe);
unsigned int	str_ptr_len(char **ptr);
unsigned int	fd_ptr_len(int (*fd)[2]);
unsigned int	count_infile(char *s);
unsigned int	count_specific_token(t_token *token, int code);

// Utils - Malloc free functions
void			free_t_token(t_token *token);
void			free_t_pipe(t_pipe *pipe);
void			free_str_ptr(char **ptr);
void			free_one_t_token(t_token *token);
t_token			*last_token(t_token *lst);

// Utils - Tokens structure manipulation
t_token			*ft_token_new(char *str, int token);
void			ft_token_add_front(t_token **token, t_token *new);
void			ft_token_add_back(t_token **token, t_token *new);
t_token			*ft_token_copy(t_token *token);

// Utils - Pipes structure manipulation
void			ft_pipe_display(t_pipe *pipes);
void			ft_pipe_add_front(t_pipe **pipe, t_pipe *new);
void			ft_pipe_add_back(t_pipe **pipe, t_pipe *new);
t_pipe			*ft_pipe_new(void);

// Utils - Other
char			**copy_str_ptr(char **ptr);

// Exec
void			ft_exec(t_token **tokens);

#endif
