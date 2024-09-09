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
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/utils/libft/libft.h"
# include "../src/utils/garbage_collector/includes/garbage_collector.h"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define _ENV "env"
# define EXIT "exit"

typedef enum token
{
	PIPE,
	STRING,
	REDIR_APPEND_OUT,
	HERE_DOC,
	REDIR_IN,
	REDIR_OUT,
	COMMAND,
	ENV,
	EXIT_STATUS,
	QUOTE,
	BLANK
}	e_token;

typedef struct s_token
{
	char			*str;
	e_token			token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct	s_envp
{
	char			*name;
	char			*value;
	struct	s_envp	*next;
	struct	s_envp	*prev;
}	t_envp;

typedef struct s_pipe
{
	int				fds[2];
	int				here_doc[2];
	int				pid;
	t_envp			*menvp;
	struct s_token	*tokens;
	struct s_pipe	*next;
	struct s_pipe	*prev;
}	t_pipe;

t_token			*tokenization(char *prompt);
void			parse_tokens(t_token *token, char **envp);

// Utils - Error management
void			raise_perror(char *error, int critical);
void			raise_error(char *error, char *details, int critical,
					int exit_code);

// Utils - Ptr size functions
unsigned int	token_ptr_size(t_token *token);
unsigned int	pipe_ptr_size(t_pipe *pipe);
unsigned int	menvp_ptr_size(t_envp *menvp);
unsigned int	str_ptr_len(char **ptr);
unsigned int	fd_ptr_len(int (*fd)[2]);
unsigned int	count_infile(char *s);
unsigned int	count_specific_token(t_token *token, e_token code);

// Utils - Malloc free functions
void			free_t_token(t_token *token);
void			free_t_pipe(t_pipe *pipe);
void			free_str_ptr(char **ptr);
void			free_one_t_token(t_token *token);

// Utils - Tokens structure manipulation
char			**token_struct_to_str_ptr(t_token *lst);
t_token			*ft_token_new(char *str, int token);
t_token			*ft_token_copy(t_token *token);
t_token			*last_token(t_token *lst);
void			ft_token_add_front(t_token **token, t_token *new);
void			ft_token_add_back(t_token **token, t_token *new);
void			ft_token_del(t_token **tokens, t_token *del);
void			display_tokens(t_token *lst);

// Utils - Pipes structure manipulation
t_pipe			*ft_pipe_new(t_envp *menvp);
t_token			*ft_find_token(t_pipe *pipes, e_token token);
void			ft_pipe_display(t_pipe *pipes);
void			ft_pipe_add_front(t_pipe **pipes, t_pipe *new);
void			ft_pipe_add_back(t_pipe **pipes, t_pipe *new);
void			ft_pipe_close_fds(t_pipe *pipes);
void			ft_close_pipe(int fd[2]);

// Utils - Envp structure manipulation
t_envp			*init_envp(char **envp);
t_envp			*t_envp_new(char *name, char *value);
void			t_envp_add_back(t_envp **envp, t_envp *new);
void			t_envp_add_front(t_envp **envp, t_envp *new);
void			t_envp_display(t_envp *envp);
char			**create_str_envp(t_envp *menvp);

// Utils - Builtins
int				is_command_builtin(char *cmd);
void			ft_echo(char **cmd);
void			ft_pwd(void);
void			ft_cd(char **cmd);
void			ft_env(t_envp *menvp);
void			ft_unset(t_envp *menvp, char *to_unset);
void			ft_export(char **cmd, t_envp *menvp);

// Utils - Exec
t_pipe			*prepare_pipes(t_token **tokens, t_envp *menvp);
void			token_management(t_pipe *pipes, t_token *token);

// Utils - Other
char			**copy_str_ptr(char **ptr);
char			*find_path(char **cmd, char **envp);

// Exec
t_token			*ft_here_doc(t_pipe *pipes, t_token *token);
t_token			*ft_redir_in(t_pipe *pipes, t_token *token, int *fdin);
t_token			*ft_redir_out(t_pipe *pipes, t_token *token, int *fdout);
void			ft_check_redir_in_out(t_pipe *pipes, int fdin, int fdout);
void			exec_main_processus(t_pipe *pipes);
void			exec_sub_processus(t_pipe *pipes, unsigned int size,
					unsigned int i);
void			exec_builtins(t_pipe *pipes, char **cmd);
void			ft_exec(t_token **tokens, t_envp *menvp);

#endif
