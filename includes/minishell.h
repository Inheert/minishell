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

typedef struct s_envp
{
	char			*name;
	char			*value;
	int				equal;
	struct s_envp	*next;
	struct s_envp	*prev;
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

t_token			*tokenisation(char *prompt);
void			blanks(t_token *token, char *prompt, int *i);
void			simple_quote(t_token *token, char *prompt, int *i);
int				parse_tokens(t_token *token, t_envp *menvp);
void			join_tokens(t_token *token);
void			clean_blank(t_token **token);
void			put_cmd(t_token *token);

// Utils - Error management
void			raise_perror(char *error, int critical);
void			raise_error(char *error, char *details, int critical,
					int exit_code);

// Utils - Ptr size functions
unsigned int	t_token_size(t_token *token);
unsigned int	t_pipe_size(t_pipe *pipe);
unsigned int	t_envp_size(t_envp *menvp);
unsigned int	str_ptr_size(char **ptr);
unsigned int	fd_ptr_size(int (*fd)[2]);
unsigned int	count_infile(char *s);
unsigned int	t_token_count_specific(t_token *token, e_token code);

// Utils - Malloc free functions
void			free_t_token(t_token *token);
void			free_t_pipe(t_pipe *pipe);
void			free_str_ptr(char **ptr);
void			free_one_t_token(t_token *token);
void			free_t_envp(t_envp *menvp);

// Utils - Tokens structure manipulation
char			**t_token_to_str_ptr(t_token *lst);
t_token			*t_token_new(char *str, int token);
t_token			*t_token_copy(t_token *token);
t_token			*t_token_last(t_token *lst);
void			t_token_add_front(t_token **token, t_token *new);
void			t_token_add_back(t_token **token, t_token *new);
void			t_token_del(t_token **tokens, t_token *del);
void			t_token_display(t_token *lst);

// Utils - Pipes structure manipulation
t_pipe			*t_pipe_new(t_envp *menvp);
t_token			*t_token_finding(t_pipe *pipes, e_token token);
void			t_pipe_display(t_pipe *pipes);
void			t_pipe_add_front(t_pipe **pipes, t_pipe *new);
void			t_pipe_add_back(t_pipe **pipes, t_pipe *new);
void			t_pipe_close_fds(t_pipe *pipes);
void			t_close_pipe(int fd[2]);

// Utils - Envp structure manipulation
t_envp			*init_envp(char **envp);
t_envp			*t_envp_new(char *name, char *value, int no_char_equal);
void			t_envp_add_back(t_envp **envp, t_envp *new);
void			t_envp_add_front(t_envp **envp, t_envp *new);
void			t_envp_update(t_envp **menvp, t_envp *new);
void			t_envp_display(t_envp *envp);
int				t_envp_is_exist(t_envp *menvp, char *name);
t_envp			*t_envp_finding(t_envp *menvp, char *name);
char			*concat_str_equal_sign(char **str);
char			**create_str_envp(t_envp *menvp);

// Utils - Builtins
int				is_command_builtin(char *cmd);
void			ft_echo(char **cmd);
void			ft_pwd(void);
void			ft_cd(t_envp *menvp, char **cmd);
void			ft_env(t_envp *menvp);
void			ft_unset(t_envp *menvp, char *to_unset);
void			ft_export(char **cmd, t_envp *menvp);
void			ft_exit(char **code);

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
void			exec_first_processus(t_pipe *pipes);
void			exec_middle_processus(t_pipe *pipes);
void			exec_last_processus(t_pipe *pipes);
void			exec_builtins(t_pipe *pipes, char **cmd, int sub_process);
void			ft_exec(t_token **tokens, t_envp *menvp);

#endif
