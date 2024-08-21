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
# include <sys/wait.h>
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

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define _ENV "env"
# define EXIT "exit"

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
	int				redir_in;
	int				redir_out;
	int				standard_input;
	int				standard_output;
	int				pid;
	struct s_pipe	*next;
	struct s_pipe	*prev;
}	t_pipe;

t_token			*tokenization(char *prompt);
void			parse_tokens(t_token *token);
char			*first_word_next_token(t_token *token);
char			*delete_first_word(char *str);

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

// Utils - Tokens structure manipulation
t_token			*ft_token_new(char *str, int token);
t_token			*ft_token_copy(t_token *token);
t_token			*last_token(t_token *lst);
void			ft_token_add_front(t_token **token, t_token *new);
void			ft_token_add_back(t_token **token, t_token *new);

// Utils - Pipes structure manipulation
t_pipe			*ft_pipe_new(void);
t_token			*ft_find_token(t_pipe *pipes, int token);
void			ft_pipe_display(t_pipe *pipes);
void			ft_pipe_add_front(t_pipe **pipes, t_pipe *new);
void			ft_pipe_add_back(t_pipe **pipes, t_pipe *new);
void			ft_pipe_close_fds(t_pipe *pipes);
int				get_actual_input(t_pipe *pipes, int set);
int				get_actual_output(t_pipe *pipes, int set);

// Utils - Builtins
int				is_command_builtin(char *cmd);
void			ft_echo(char **cmd);

// Utils - Other
char			**copy_str_ptr(char **ptr);
char			*find_path(char **cmd, char **envp);
char			*ft_first_word(char *str);

// Exec
void			exec_builtins(char **cmd);
void			ft_exec(t_token **tokens, char **envp);

#endif
