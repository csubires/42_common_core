/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:22 by csubires          #+#    #+#             */
/*   Updated: 2025/02/19 18:06:33 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include "libft/libft.h"
# include "dlinked_list/dlinked_list.h"

# define ERR_ARG			"the args for this program are not available\n"
# define ERR_MALLOC			"error to create malloc\n"
# define ERR_MANY			"too many arguments\n"
# define ERR_UP_ENV			"error when updating the environment variable\n"
# define ERR_PATH			"no such file or directory\n"
# define ERR_NOTCMD			"command not found\n"
# define ERR_CHILD			"command not found\n"
# define ERR_FORK			"exec_parent fork error\n"
# define ERR_FD				"error manage fd\n"
# define ERR_ASIG			"bad assignment\n"
# define ERR_QUOT			"error unclosed quotation marks detected\n"
# define ERR_FIRST_QUOTE	"invalid imput with start quote\n"
# define ERR_EXPO			"not a valid identifier\n"
# define ERR_TOKEN			"syntax error near unexpected token\n"
# define ERR_EXIT			"numeric argument required\n"
# define ERR_EVNOTF			"environment variables not found\n"

# define RED				"\033[1;31m"
# define GREEN				"\033[1;32m"
# define YELLOW				"\033[1;33m"
# define BLUE				"\033[1;34m"
# define ENDC				"\033[0m"

typedef struct s_envp
{
	char		*key;
	char		*value;
}				t_envp;

typedef struct s_exec
{
	t_dllist	*arg_list;
	char		*executable;
	char		*heredoc_delimiter;
	char		*heredoc_data;
	char		*input_file;
	char		*output_file;
	int			in_fd;
	int			out_fd;
	int			append_to_fd;
}				t_exec;

typedef struct s_shell
{
	t_dllist	*env_list;
	t_dllist	*token_list;
	t_dllist	*exec_list;
	t_dllist	*childrenpid_list;
	char		*input;
	int			num_of_cmds;
	int			exit_stat;
	int			error;
}				t_shell;

//			BUILD_INS/*.C
void		buildin_exit(t_shell *shell, t_exec *exec_cmd);
size_t		buildin_cd(t_shell *shell, t_exec *exec_cmd);
size_t		buildin_echo(t_shell *shell, t_exec *exec_cmd);
size_t		buildin_env(t_shell *shell, t_exec *exec_cmd);
size_t		buildin_export(t_shell *shell, t_exec *exec_cmd);
size_t		buildin_pwd(t_shell *shell, t_exec *exec_cmd);
size_t		buildin_unset(t_shell *shell, t_exec *exec_cmd);

//			BUILD_INS/BUILDIN_UTILS.C
void		free_copy_list(t_dllist *head);
void		update_envp(t_dllist *node, char *new_value);

//			ENVIRONMENT/ENVP.C
t_dllist	*search_env_item(t_dllist *env_list, char *key);
t_envp		*create_env_item(char *key_value[]);
char		*get_env_value(t_dllist *env_list, char *key);
void		insert_env_item(t_shell *shell, t_envp *item);
void		envp_to_dllist(t_shell *shell, char *envp[]);

//			ENVIRONMENT/ENVP_UTILS.C
char		**split_env_item(char *envp, char separator);
void		free_env_entry(void *entry);
void		check_args(int argc, char *envp[]);

//			EXECUTOR/EXECUTOR.C
void		execute_execs(t_shell *shell);

//			EXECUTOR/EXECUTOR_UTILS.C
char		**args_to_array(t_exec *exec_cmd);
char		**envp_to_array(t_shell *shell);
int			is_builtin(char *exec_str);

//			EXECUTOR/CHILD.C
void		execute_child(t_shell *shell, char **env, char **arg, \
			t_exec *exec_cmd);

//			EXECUTOR/CHILD_UTILS.C
char		*get_path_exec(t_shell *shell, char *exec_str);
void		free_array(void *array[]);

//			EXECUTOR/FDS.C
void		manage_fds(t_shell *shell);

//			EXECUTOR/FDS_UTILS.C
void		manage_output_fd(t_exec *exec_cmd, t_dllist *tmp_list);
void		manage_heredoc(t_shell *shell);

//			INPUT/EXPANDER.C
char		*ft_strreplace(char *str, int start, int end, char *substr);
void		expand_envp(t_shell *shell, int *x);

//			INPUT/LEXER.C
int			split_tokens(t_shell *shell, char *input);
void		replace_with_envp(t_shell *shell);
void		tokens_to_dllist(t_shell *shell);

//			INPUT/LEXER_UTILS.C
void		token_to_dllist(t_shell *shell, int start, int end, \
			char before_quote);
void		set_redirect(t_shell *shell, char *input, int *x);
void		tokenise_arg(t_shell *shell, char *input, int *x);
int			isnt_metachar(char c);

//			INPUT/LEXER_UTILS_2.C
int			token_to_dllist_check(t_shell *shell);
void		replace_value(t_shell *shell, int *x, char *key, \
			char *value);
int			check_double_quote(t_shell *shell);
void		repare_executable(t_exec *exec_cmd, t_dllist *tmp_list2);
void		set_redirect2(t_shell *shell, char *input, int *x);

//			INPUT/PARSER.C
void		exec_cmd_to_dllist(t_shell *shell);

//			INPUT/PARSER_UTILS.C
void		manage_redirection(t_exec *exec_cmd, t_dllist *token_ptr[]);

//			UTILS/FREE.C
void		free_tokens(t_shell *shell);
void		free_all(t_shell *shell);
void		free_data(void *data);
void		free_execs(void *item);

//			UTILS/SIGNALS.C
void		init_signals(void);
void		restore_signals(void);

//			UTILS/UTILS.C
int			is_empty(char *str);
int			print_error(int err, t_shell *shell, char *msg, char *func);
int			file_exists(char *file_name);

#endif
