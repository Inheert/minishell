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

# define _GNU_SOURCE

// Include the necessary libraries
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../src/utils/libft/libft.h"
# include "../src/utils/garbage_collector/includes/garbage_collector.h"

// Define builtins constants
# define _ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define _ENV "env"
# define EXIT "exit"

// Enum used to define all token types
typedef enum e_type
{
	PIPE,
	REDIR_APPEND_OUT,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	FILLE,
	BUILTIN,
	COMMAND,
	STRING,
}	t_token_type;

// Token structure used in the execution.
// char *str		-> is used to store the string related to the token type.
// t_token_type token ->  is used to store the token type.
// struct s_token *next	-> next token.
// struct s_token *prev	-> previous token.
typedef struct s_token
{
	char			*str;
	t_token_type	token;
	int				flag_quotes;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Envp structure used to store and easily manipulate envs vars.
// char *name	-> env var name.
// char	*value	-> env var value.
// int	equal	-> is the symbol '=' was present during the declaration,
//				it is used to adapt the var display when using env or export.
// struct s_envp *next	-> next env var.
// struct s_envp *prev	-> previous env var.
typedef struct s_envp
{
	char			*name;
	char			*value;
	int				equal;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

/* help_norme */
typedef struct s_help
{
	char	**table;
	char	*result;
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	len1;
	int		start;
	int		count;
	size_t	size_str;
	size_t	len_en_moins;
	size_t	len_en_plus;
	char	*is_dol;
	char	**split;
	t_envp	*node_env;
}	t_help;

typedef struct s_quote_expand_helper
{
	char	*current_str;
	char	*word;
	char	c;
	int		in_single_quote;
	int		in_double_quote;
	int		last_quote;
	int		concatenate_quote;
	int		i;
	int		j;
}	t_quote_expand_helper;

// processus structure used to store data related to each processus.
// int fds[2]		-> pipe fds storage.
// int heredoc[2]	-> heredoc fds storage.
// int pid			-> store the processus id.
// int parent_id	-> store the parent processus id.
// int status_code	-> used to store the last exit code of a processus/command.
// t_envp *menvp	-> env var structure.
// t_token *tokens	-> all tokens related to the processus.
// struct s_processus *next -> next processus.
// struct s_processus *prev -> previous processus.
typedef struct s_processus
{
	int					fds[2];
	int					heredoc[2];
	int					pid;
	int					parent_pid;
	int					status_code;
	t_envp				**menvp;
	t_token				*tokens;
	struct s_processus	*next;
	struct s_processus	*prev;
}	t_processus;

typedef enum s_signal_type
{
	READLINE,
	HEREDOC_SIG,
	FORK,
	SILENCE,
	DEFAULT
}	t_signal_type;

// Signals handlers prototypes
extern int		g_signal_code;
void			set_signals(t_signal_type mode);

// Lexer handlers
int				handle_quotes_table(char **result, const char *line,
					t_help *h, char quote_char);
int				handle_specials_or_spaces_table(char **result,
					const char *line, t_help *h);
int				handle_quotes(const char *line, int *i, t_help *h,
					char quote_char);
int				handle_specials_or_spaces(const char *line, int *i, t_help *h);

// Find token type
int				change_after_red(t_token *token, int *after_red);
t_token_type	find_type(t_token *tmp, int *after_red);
int				look_for_dol(char *s);
int				find_token_type(t_token **tokens, t_envp *menvp);

// Tokenizer_help
int				manage_quotes(char c, int *in_double_quote,
					int *in_single_quote, int *last_quote);
int				manage_env_var_expand(char **current_str, char *word, int *j,
					t_envp *menvp);
int				concat_token_redir(t_token **tokens);

char			**manage_lexer(const char *line);
t_token			*manage_tokenizer(char **lexer);
void			print_lexer(char *line, char **lexer);
t_token			*process_quotes(char **lexer, t_envp *menvp);

//  ________  ____  ____  ________    ______
// |_   __  ||_  _||_  _||_   __  | .' ___  |
//   | |_ \_|  \ \  / /    | |_ \_|/ .'   \_|
//   |  _| _    > `' <     |  _| _ | |
//  _| |__/ | _/ /'`\ \_  _| |__/ |\ `.___.'
// |________||____||____||________| `.____ .'

// Take the address of the original tokens ptr and var env as arg.
// Used to start the execution of the current command line.
void			command_line_exec(t_token **tokens, t_envp **menvp);

// Take the actual processus as arg.
// Manage the first processus.
void			exec_first_processus(t_processus *process);

// Take the actual processus as arg.
// Manage all middle processus.
void			exec_middle_processus(t_processus *process);

// Take the actual processus as arg.
// Manage the last processus.
void			exec_last_processus(t_processus *process);

// Take the actual processus, the command + args and a bool
// if this is a sub_processus as arg.
// Manage the execution of builtins.
void			exec_builtins(t_processus *process, char **cmd,
					int sub_process);

// Take processus ptr (all of them) struct as arg
// Create fds for heredocs of each process and write in it.
void			manage_heredocs(t_processus *process);

// Take the actual processus struct, redir token and a ptr to int as arg.
// Open the new infile and close the old one if exists.
t_token			*manage_redir_in(t_processus *process, t_token *token,
					int *fdin);

// Take the actual processus struct, redir token and a ptr to int as arg.
// Open the new outfile and close the old one if exists.
t_token			*manage_redir_out(t_processus *process, t_token *token,
					int *fdout);

// Take the actual processus struct, redir in and out as arg.
// Dup2 the standard input and output by the last infile/heredoc or outfile.
void			ft_check_redir_in_out(t_processus *process, int fdin,
					int fdout);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
//  ________
// |_   __  |
//   | |_ \_| _   __  .---.  .---.
//   |  _| _ [ \ [  ]/ /__\\/ /'`\]
//  _| |__/ | > '  < | \__.,| \__.
// |________|[__]`\_] '.__.''.___.'

// Take the address of the original t_token ptr and a t_envp ptr as arg.
// Used to prepare t_processus (struct processus used for the execution) by
// dividing token for each process, manage heredoc, etc
t_processus		*prepare_processus(t_token **tokens, t_envp **menvp);

int				does_fds_count_exceed_the_limit(t_processus *process);

// Take the t_processus ptr (actual processus struct details), a t_token ptr and
// a bool to know if we are in a sub_process or not.
// This function manage all redirection dup2 like <, >, >> and <<.
void			token_management(t_processus *process, t_token *token,
					int is_sub_process);

// Take a char ** (command + arg) and another char ** (envp) as arg.
// This function is used to find the actual path of the command and return it.
char			*find_path(char **cmd, char **envp);

// Take a t_processus ptr as arg.
// This function return a bool, if there is a redir in (infile, heredoc) in the
// given process it return 1, else 0.
int				is_redir_in_priority(t_processus *process);

// Take a t_processus ptr as arg.
// Function used to delete all REDIR (in, out, append, heredoc) tokens,
// when this func is used those tokens are useless and avoid the program
// to work properly so we delete them.
void			delete_useless_tokens(t_processus *process);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
//  ________
// |_   __  |
//   | |_ \_| _ .--.  _ .--.   .--.   _ .--.
//   |  _| _ [ `/'`\][ `/'`\]/ .'`\ \[ `/'`\]
//  _| |__/ | | |     | |    | \__. | | |
// |________|[___]   [___]    '.__.' [___]

// Utils - Error management

// Take a int and a t_envp ptr as arg.
// This function is used to set the env var $? with the last status
// code, it take a ptr to the env var structure that is stored as a static
// to avoid us giving the env structure each time we set the status code.
void			set_exit_status(int code, t_envp **menvp);

// Take a char * (the error) and a bool if the processus should exit
// or not as arg.
// raise an error using perror and exit using errno if critical.
void			raise_perror(char *error, int critical);

// take a char * (the error), another char * (the error details),
// a bool if the processus should exit, and the exit code as arg.
// raise an custom error that are normally not set via errno
// and exit the program if critical.
void			raise_error(char *error, char *details, int critical,
					int exit_code);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
//  _            _          __
// / |_         / |_       [  |  _
//`| |-'       `| |-' .--.  | | / ] .---.  _ .--.
// | |          | | / .'`\ \| '' < / /__\\[ `.-. |
// | |, _______ | |,| \__. || |`\ \| \__., | | | |
// \__/|_______|\__/ '.__.'[__|  \_]'.__.'[___||__]

// Take a t_token ptr as arg.
// Convert and return the chained list as a char **.
char			**t_token_to_str_ptr(t_token *lst);

// Take a char * and the token type as arg.
// Create and return a new t_token.
t_token			*t_token_new(char *str, int token, int flag_quotes);

// Take a t_token ptr as arg.
// Copy the arg token WITHOUT linking it and return it.
t_token			*t_token_copy(t_token *token);

// Take a t_token ptr as arg.
// Return the last token of the chained list.
t_token			*t_token_last(t_token *lst);

// Take the address of the original t_token ptr and a new token as arg.
// Add it at the start of the chained list.
void			t_token_add_front(t_token **token, t_token *new);

// Take the address of the original t_token ptr and a new token as arg.
// Add it at the end of the chained list.
void			t_token_add_back(t_token **token, t_token *new);

// Take the address of the original t_token ptr and a token as arg.
// Remove the second t_token arg from the chained list.
void			t_token_del(t_token **tokens, t_token *del);

// Take a t_token ptr as arg.
// Display all the chained list on the standard output, used for debug.
void			t_token_display(t_token *lst);

// Take a t_token ptr as arg.
// Return the size of the actual chained list, if arg is NULL return 0.
unsigned int	t_token_size(t_token *token);

// Take a t_token ptr and a token type as arg.
// Return the count of the specific token type in the chained list.
unsigned int	t_token_count_specific(t_token *token, t_token_type code);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
//  _                     _
// / |_                  (_)
//`| |-'        _ .--.   __  _ .--.   .---.
// | |         [ '/'`\ \[  |[ '/'`\ \/ /__\\.
// | |, _______ | \__/ | | | | \__/ || \__.,
// \__/|_______|| ;.__/ [___]| ;.__/  '.__.'
//             [__|         [__|

// Take a t_envp ptr as arg.
// Create a new t_processus struct (processus structure)
t_processus		*t_processus_new(t_envp **menvp);

// Take a t_processus ptr and a token type as arg.
// Return the first token found with the token type arg in the t_processus
// struct, else return NULL.
t_token			*t_token_finding(t_token *tokens, t_token_type token);

// Take a t_processus ptr as arg.
// Display all the chained list on the standard output, used for debug.
void			t_processus_display(t_processus *process);

// Take the address of the original t_processus ptr and a
// new t_processus as arg. Add it at the start of the chained list.
void			t_processus_add_front(t_processus **process, t_processus *new);

// Take the address of the original t_processus ptr and
// a new t_processus as arg. Add it at the end of the chained list.
void			t_processus_add_back(t_processus **process, t_processus *new);

// Take a t_processus ptr as arg.
// Close the fds of ALL t_processus, it loop to t_processus->prev
// until no prev exist.
void			t_processus_close_fds(t_processus *process);

// Take a t_processus ptr as arg.
// Specifically used to close fds for builtins when used in the main processus.
void			t_processus_close_builtin_fds(t_processus *process);

// Take a t_processus ptr as arg.
// Return the size of the chained list, if arg is NULL return 0.
unsigned int	t_processus_size(t_processus *pipe);

// Take a t_processus ptr as arg and the fd type (input / output, 0 / 1) as arg.
// Return the standard input/output for the actual process.
// If t_processus ptr is NULL or there is no infile / outfile then the
// standard input / output is returned.
int				get_fds(t_processus *process, int fd);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
//  _
// / |_
//`| |-'        .---.  _ .--.  _   __  _ .--.
// | |         / /__\\[ `.-. |[ \ [  ][ '/'`\ \.
// | |, _______| \__., | | | | \ \/ /  | \__/ |.
// \__/|_______|'.__.'[___||__] \__/   | ;.__/
//                                    [__|

// Take a char ** (envp main arg) as arg.
// Create and return a t_envp struct used to more easily manipulate envs vars.
t_envp			*t_envp_init(char **envp);
void			t_envp_init_2(t_envp **menvp, char **envp);

// take a char * (env name), another char * (env value) and a bool used to make
// the difference between a var without any value nor equal and a var with value
// or equal.
// Example :
//	- ABC		-> t_envp_new("ABC", NULL, 1);
//	- ABC=		-> t_envp_new("ABC", NULL, 0);
//	- ABC=DEF	-> t_envp_new("ABC", "DEF", 0);
t_envp			*t_envp_new(char *name, char *value, int no_char_equal);

// Take the address of the original t_envp ptr and a new t_envp as arg.
// Add it at the start of the chained list.
void			t_envp_add_front(t_envp **envp, t_envp *new);

// Take the address of the original t_envp ptr and a new t_envp as arg.
// Add it at the end of the chained list.
void			t_envp_add_back(t_envp **envp, t_envp *new);

// Take the address of the original t_envp to replace and a new t_envp as arg.
// Used to update the existing menvp var (first arg) by the second one.
void			t_envp_update(t_envp *menvp, t_envp *new);

// Take a t_envp ptr as arg.
// Display all the chained list on the standard output, used for debug.
void			t_envp_display(t_envp *envp);

// Take a t_envp ptr and a char * (env name) as arg.
// Return 1 if the env var exist else 0.
int				t_envp_is_exist(t_envp *menvp, char *name);

// Take a t_envp ptr and a char * (env name) as arg.
// Return the t_envp ptr with the same name as the second arg if it exists,
// else return NULL.
t_envp			*t_envp_finding(t_envp *menvp, char *name);

// Take a char ** as arg.
// This function is specificaly used to reconcate a char ** that have been split
// using ft_split(char **, '=').
char			*concat_str_equal_sign(char **str);

// Take a t_envp ptr as arg.
// Convert the t_envp chained list to char ** and return it.
char			**t_envp_convert_to_str(t_envp *menvp);

// Take a t_envp struct as arg.
// Return the size of the chained list, if ptr is NULL return NULL.
unsigned int	t_envp_size(t_envp *menvp);

// Take a t_envp struct as arg.
// This function is used to check if the current working directory still exist,
// if not it update pwd to avoid problems in the execution.
void			t_envp_check(t_envp *menvp);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
// __                  _   __   _    _
//[  |                (_) [  | / |_ (_)
// | |.--.   __   _   __   | |`| |-'__   _ .--.   .--.
// | '/'`\ \[  | | | [  |  | | | | [  | [ `.-. | ( (`\]
// |  \__/ | | \_/ |, | |  | | | |, | |  | | | |  `'.'.
//[__;.__.'  '.__.'_/[___][___]\__/[___][___||__][\__) )

// Take a char * as arg (the command).
// Return 1 if the command is a builtin else 0.
int				is_command_builtin(char *cmd);

// Take a char ** (command + arg) and a t_processus ptr as arg.
// Reproduce the bash echo command.
void			ft_echo(char **cmd, t_processus *process);

// Take a t_processus ptr as arg.
// Reproduce the bash pwd command.
void			ft_pwd(t_processus *process);

// Take a t_envp ptr and a char ** (command + arg) as arg.
// Reproduce the bash cd command.
void			ft_cd(t_envp *menvp, char **cmd);

// Take a t_processus ptr and a t_envp ptr as arg.
// Reproduce the bash env command.
void			ft_env(t_processus *process, t_envp *menvp);

// Take t_envp ptr and a char * (env var to unset) as arg.
// Reproduce the bash unset command.
void			ft_unset(t_envp **menvp, char **to_unset);

// Take a char ** (command + arg), a t_processus ptr and a t_envp ptr as arg.
// Reproduce the bash export command.
void			ft_export(char **cmd, t_processus *process, t_envp *menvp);
int				manage_new_var(char **cmd, char *equal, t_envp *menvp, int i);

// Take a t_processus ptr as arg and a char ** (command args) as arg.
// Reproduce the bash exit command.
void			ft_exit(t_processus *process, char **code);

//  _____  _____  _    _   __
// |_   _||_   _|/ |_ (_) [  |
//   | |    | | `| |-'__   | |  .--.
//   | '    ' |  | | [  |  | | ( (`\]
//    \ \__/ /   | |, | |  | |  `'.'.
//     `.__.'    \__/[___][___][\__) )
//  ________                           ___
// |_   __  |                        .' ..]
//   | |_ \_|_ .--.  .---.  .---.   _| |_  __   _   _ .--.   .---.
//   |  _|  [ `/'`\]/ /__\\/ /__\\ '-| |-'[  | | | [ `.-. | / /'`\]
//  _| |_    | |    | \__.,| \__.,   | |   | \_/ |, | | | | | \__.
// |_____|  [___]    '.__.' '.__.'  [___]  '.__.'_/[___||__]'.___.'

// Used to free a t_token struct properly.
void			free_one_t_token(t_token *token);

// Used to free all t_token chained list properly.
void			free_t_token(t_token *token);

// Used to free all t_processus chained list properly.
void			free_t_processus(t_processus *pipe);

// Used to free a char ** properly.
void			free_str_ptr(char **ptr);

// Used to free all t_envp chained list properly.
void			free_t_envp(t_envp *menvp);

//    ___     _   __
//  .'   `.  / |_[  |
// /  .-.  \`| |-'| |--.  .---.  _ .--.
// | |   | | | |  | .-. |/ /__\\[ `/'`\]
// \  `-'  / | |, | | | || \__., | |
//  `.___.'  \__/[___]|__]'.__.'[___]

// Return the size of a char **.
unsigned int	str_ptr_size(char **ptr);

#endif
