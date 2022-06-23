#ifndef MINISHELL_H
# define MINISHELL_H

/*
 ** =========[ Includes ]==========
 */

# include "libft.h"

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/*
 ** =========[ Defines ]===========
 */

/*
 ** [ TOKENS ]
 **
 ** WHITE_SPACE ' '
 ** PIPE        '|'
 ** DOLLAR      '$'
 ** QUOTE       '''
 ** D_QUOTE     '"'
 ** GREAT       '>'
 ** D_GREAT     '>>'
 ** LESS        '<'
 ** D_LESS      '<<'
 ** FILE        'file'
 ** S_WORD      'EOF'
 ** WORD        'str'
 */

# define WS 0
# define PP 1
# define DO 2
# define QT 3
# define DQ 4
# define GT 5
# define DG 6
# define LS 7
# define DL 8
# define FI 9
# define SW 10
# define WD 11

/*
 ** [ RETURN ]
 */

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1

/*
 ** =========[ Structures ]========
 */

/*
 ** Tokens
 */

typedef struct s_tok
{
	int		tokid;
	int		tokpos;
	char	*tok;

}			t_tok;

/*
 ** Environ
 */

typedef struct s_env
{
	char	*key;
	char	*val;

}			t_env;

/*
 ** Commands
 */

typedef struct s_cmd
{
	int		error;
	int		cmdid;
	int		cmdpos;
	size_t	nb_arg;
	char	**cmd;
	char	*prg;

	int		fd[2];

	int		type_in;
	int		type_out;

	char	*file_in;
	char	*file_out;

	char	*stop_word;
	int		is_here_doc;

	int		fd_in;
	int		fd_out;

}			t_cmd;

/*
 ** Export
 */

typedef struct s_exp
{
	char	*key;
	char	*val;

}			t_exp;

/*
 ** Redirection TODO:USELESS?
 */

typedef struct s_redir
{
	int				type;
	int				cmdid;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;

}				t_redir;

/*
 ** Data
 */

typedef struct s_data
{
	int		cmdid;
	int		cmdcount;
	char	*cmdline;
	char	**environ;
	char	**envtab;

	t_dlist	*toklist;
	t_dlist	*cmdlist;
	t_dlist	*envlist;
	t_dlist	*explist;
	t_dlist	*redlist;

	char	*cwd;
	char	*oldcwd;

	int		nb_pipes;
	char	*cwdpath;
	char	**cmd_path;
	int		last_in;
	int		last_out;

	int		shlvl;
	int		status;

}			t_data;

/*
 ** =========[ Prototypes ]========
 */

/*
 ** [ utils/utils.c ]
 */

char	*ft_w_substr (char const *s, unsigned int start, size_t len, t_data *data);
char	*ft_w_strdup (const char *s1, t_data *data)

char	*ft_strjoin_free_s2(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_free(void *ptr);
void	ft_free_tab(char **tab);
void	*ft_backfree(char **tab, int i);
void	ft_exitmsg (t_data *data, char *str);
void	ft_clear_exit(t_data *data);
void	ft_dlst_elem_dup(t_data *data, t_dlist **lst, t_dlist *dup);

/* #----------------------------------------------------------------------# */
/* #                  BUILTINS                                            # */
/* #----------------------------------------------------------------------# */

/*
 ** [ builtin/exit.c ]
 */

void    ft_exit(t_data *data, char **cmd);

/*
 ** [ builtin/cd.c ]
 */

int		ft_cd(t_data *data, char **cmd);

/*
 ** [ builtin/pwd.c ]
 */

int		ft_pwd(t_data *data);

/*
 ** [ builtin/export.c ]
 */

/* static void	ft_explist_export_2 (t_data *data, char *key, char *val) */
/* static void	ft_explist_export (t_data *data, char *cmd) */
/* static void	ft_envlist_export(t_data *data, char *cmd) */
/* static int	ft_is_valid_export(char *key) */
int		ft_export(t_data *data, char **cmd);

/*
 ** [ builtin/unset.c ]
 */

/* static void	ft_explist_unset(t_data *data, char *key) */
/* static void	ft_envlist_unset(t_data *data, char *key); */
/* static int	ft_is_valid_unset(char *key) */
int		ft_unset(t_data *data, char **args);

/*
 ** [ builtin/echo.c ]
 */

int		ft_is_n_flag(char *arg);
int		ft_echo(t_data *data, char **arg);

/*
 ** [ builtin/env.c ]
 */

char	**ft_update_envtab (t_data *data);
int		ft_env(t_dlist *envlist);

/* #----------------------------------------------------------------------# */
/* #                  EXECUTION                                           # */
/* #----------------------------------------------------------------------# */

/*
 ** [ exec/exec.c ]
 */

int	ft_exec(t_data *data);

/*
 ** [ exec/exec_builtin.c ]
 */

int ft_fork_builtin(t_dlist *cmd);
int ft_is_builtin(t_dlist *cmd);
int ft_exec_builtin(t_data *data, t_dlist *cmd, int builtin_id);

/*
 ** [ exec/file.c ]
 */

int		ft_open(t_data *data, t_dlist *cmd);
void    ft_close(t_data *data, t_dlist *cmd, int *fd);

/*
 ** [ exec/error.c ]
 */

void	ft_file_error(t_data *data, char *file, int error);
void    ft_cmd_error(t_dlist *cmd, int error);
void    ft_perror(t_data *data, t_dlist *cmd, int error);

/*
 ** [ exec/close.c ]
 */

void    ft_close_fd(t_data *data, t_dlist *cmd);
void    ft_close_std(void);
void    ft_close_all(t_data *data, t_dlist *cmd);

/* #----------------------------------------------------------------------# */
/* #                  PARSER                                              # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/cmdlist.c ]
 */

void	ft_create_cmdlist(t_data *data);
void	ft_add_cmd(t_data *data);
void	ft_printlist_cmd(t_dlist *cmdlist);
void	ft_clearlist_cmd(t_dlist **cmdlist, void (*del)(void *));

/*
 ** [ parser/parser_utils.c ]
 */

int		ft_is_tokid(t_dlist *toklist, int tokid);

/*
 ** [ parser/parse_command.c ]
 */

char	*ft_expand_cwd (char *command);
char	*ft_command(t_data *data, char *command);
char	**ft_arg_cmd(t_data *data, t_dlist **cmd, t_dlist **toklist);
void	ft_parse_command(t_data *data);

/*
 ** [ utils/pipe.c ]
 */

void	ft_count_pipe(t_data *data);

/*
 ** [ parser/expand_tilde.c ]
 */

void	ft_expand_tilde(t_data *data);

/*
 ** [ parser/expand_word.c ]
 */

/* static char *ft_concat_all_words(t_dlist *toklist) */
void	ft_expand_word(t_data *data);

/*
 ** [ utils/redlist.c ]
 */

void	ft_create_redlist(t_data *data);
void	ft_add_red(t_data *data, t_dlist *token, int nb_cmd);
void	ft_printlist_redir(t_dlist *lst);
void	ft_clearlist_red(t_dlist **lst, void (*del)(void *));

/*
 ** [ parser/parse_redir.c ]
 */

void	ft_parse_redir(t_data *data);

/*
 ** [ parser/parse_space.c ]
 */

/* static void	ft_remove_spaces(t_data *data); */
void	ft_parse_space(t_data *data);

/*
 ** [ parser/expand_quote.c ]
 */

/* static char	*ft_concat_quoted_words(t_dlist *toklist); */
/* static void	ft_remove_empty_quotes(t_data *data); */
/* static void	ft_expand_quote2(t_dlist **new, t_dlist **temp) */
void	ft_expand_quote(t_data *data);

/*
 ** [ parser/expand_var.c ]
 */

/* static char *ft_expand_var(t_data *data, char *key) */
/* static void ft_remove_dollar(t_data *data) */
/* static void ft_heredoc_dollar(t_data *data) */
/* static void ft_simple_quote(t_data *data) */
/* static void ft_expand_dollar(t_data *data) */
/* static void ft_var_exit_status(t_data *data) */
/* static void ft_multiple_dollar(t_data *data) */
void	ft_expand_vars(t_data *data);

/*
 ** [ parser/parse_pipe.c ]
 */

/* static void	ft_trim_toklist(t_dlist *toklist, t_dlist *token); */
/* static int	ft_pre_checks(t_dlist **token) */
int		ft_parse_pipe(t_data *data);

/*
 ** [ parser/parse_quote.c ]
 */

/* static int		ft_check_last_tok(t_dlist *toklist); */
/* static void	ft_set_word_token(t_dlist **token) */
/* static void	ft_quoted_becomes_words(t_dlist *toklist); */
/* static int		ft_check_quote_pairs(t_dlist *toklist); */
int		ft_parse_quote(t_data *data, t_dlist *toklist);

/*
 ** [ parser/parser.c ]
 */

void	ft_parser(t_data *data);

/* #----------------------------------------------------------------------# */
/* #                  LEXER                                               # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/toklist.c ]
 */

void	ft_update_tokpos(t_dlist *toklist);
void	ft_remove_tok(t_dlist *toklist, t_dlist *token);
void	ft_add_tok(t_data *data, int tokid, int tokpos, char *tok);
void	ft_printlist_tok(t_dlist *toklist);
void	ft_clearlist_tok(t_dlist **toklist, void (*del)(void *));

/*
 ** [ lex/lexer.c ]
 */

/* static int	ft_set_token(char *tok) */
/* static size_t	ft_token_size(char *cmdchar) */
/* static void	ft_tokenize(t_data *data, char **cmdline, int *pos) */
void	ft_lexer(t_data *data);

/* #----------------------------------------------------------------------# */
/* #                                                                      # */
/* #----------------------------------------------------------------------# */

/*
 ** [ utils/path.c ]
 */

char	**ft_split_path(t_data *data);

/*
 ** [ utils/prompt.c ]
 */

/* static char *ft_prompt_prefix(void) */
/* static char *ft_prompt_line(t_data *data) */
/* static void ft_readline(t_data *data) */
void	ft_prompt(t_data *data);

/*
 ** [ utils/explist.c ]
 */

int		ft_check_exp_entry(t_dlist *explist, char *key);
char	*ft_getexp(t_dlist *explist, char *key);
void	ft_sort_exp(t_dlist *explist);
void	ft_update_exp(t_data *data);
void	ft_init_minimal_exp(t_data *data);
void	ft_init_exp(t_data *data);
t_dlist	*ft_remove_exp(t_dlist *explist, t_dlist *entry);
void	ft_add_exp(t_data *data, char *key, char *val);
void	ft_printlist_elem_exp(t_dlist *explist, char *key);
void	ft_printlist_exp(t_dlist *explist);
void	ft_clearlist_exp(t_dlist **explist, void (*del)(void *));

/*
 ** [ utils/envlist.c ]
 */

int		ft_check_env_entry(t_dlist *envlist, char *key);
char	*ft_getenv(t_dlist *envlist, char *key);
void	ft_update_env_pwd(t_data *data);
void	ft_init_minimal_env(t_data *data);
void	ft_init_env(t_data *data);
t_dlist	*ft_remove_env(t_dlist *envlist, t_dlist *entry);
void	ft_add_env(t_data *data, char *key, char *val);
void	ft_printlist_elem_env(t_dlist *envlist, char *key);
void	ft_printlist_env(t_dlist *envlist);
void	ft_clearlist_env(t_dlist **envlist, void (*del)(void *));

/*
 ** [ utils/tty.c ]
 */

void	ft_init_tty(void);

/*
 ** [ main.c ]
 */

/* static void	ft_init_data(t_data *data) */
void	ft_init_signals();
int		main(int ac, char **av);

#endif
