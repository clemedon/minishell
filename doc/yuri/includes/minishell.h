/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by yobougre          #+#    #+#             */
/*   Updated: 2022/06/01 14:33:20 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "includes.h"

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/signal/signal.c                         */
/* -------------------------------------------------------------------------- */
void	ft_sign_handle(int signo);
void	ft_sign_heredoc(int signo);
void	sig_choice(int a);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/utils_4.c                         */
/* -------------------------------------------------------------------------- */
int		ft_close_redirect(t_list **lst);
void	ft_quoted(t_token *token, char c);
int		ft_init_help(t_help *help, char *tmp);
void	ft_init_int(int *i, int *j);
char	*ft_swap(char *var, char *output);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/utils_3.c                         */
/* -------------------------------------------------------------------------- */
char	*ft_cut_tail(char *str);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/error.c                          */
/* -------------------------------------------------------------------------- */
void	ft_print_error(char *token);
void	ft_print_error_c(char c);
void	ft_print_ofpc(void);
void	ft_err_cd(char *path);
void	ft_err_var(char *var, int flag);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/utils_2.c                         */
/* -------------------------------------------------------------------------- */
void	ft_reset_quotes(t_token *token);
void	ft_pass_space_reverse(char *cmd, int *new_j);
char	*ft_to_str_without_free(char **str);
char	*ft_to_str(char **str);
void	ft_increm(int *i, int *j);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/utils.c                          */
/* -------------------------------------------------------------------------- */
char	**ft_dup_tab(char **tab);
int		print_pwd(void);
char	*get_pwd(void);
char	*ft_strjoin_char(char *cmd, char c);
char	*ft_strcut(char *str, int i_start, int i_end);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/utils_main.c                          */
/* -------------------------------------------------------------------------- */
int		ft_find_occ_free_help(char *var, char ***tmp);
int		ft_find_occ_free(char **env, char *var);
int		is_dpipe(t_token *token);
int		ft_hd_delete(t_list **lst);
int		ft_wait_all_pid(t_node *params, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/main.c                             */
/* -------------------------------------------------------------------------- */
int		init_shlvl(t_node *params);
int		ft_launch_exec(t_node *params, t_list **lst, t_token *token, char *cmd);
int		main(int ac, char **av, char **env);

/* -------------------------------------------------------------------------- */
/*                           FILE = srcs/refacto.c                            */
/* -------------------------------------------------------------------------- */
void	ft_we_dont(void);
void	ft_refacto_free(t_node *params, char *cmd, t_list **lst);
void	ft_refacto_help(t_token *token, int flag);
int		ft_refacto_start(t_node *parm, t_list **lst, t_token *tokn, char **cmd);
int		ft_refacto_exec(t_node *params, t_list **lst, t_token *tokn, char *cmd);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/pipes/utils_str.c                        */
/* -------------------------------------------------------------------------- */
int		ft_strlen(const char *s);
char	*ft_strdup_pimp(char *s);
int		ft_strchr_pimp(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_wrong_args(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/pipes/utils_path.c                       */
/* -------------------------------------------------------------------------- */
char	*ft_cmd(char *path, char *cmd);
int		ft_cmp_path(char *s1, char *s2);
int		get_path_pos(char **envp);
char	**get_path_lst(char **envp);
char	*check_path(char **path_lst, char *cmd);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/pipes/ft_free.c                         */
/* -------------------------------------------------------------------------- */
int		ft_tab_size(char **tab);
void	ft_free(char **tab);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/pipes/utils_exec.c                       */
/* -------------------------------------------------------------------------- */
void	ft_close_forked(t_node *params, t_list **lst);
int		ft_exec_2(t_node *params, t_list **lst, t_list **lst_to_free);
int		ft_execute(t_node *params, t_list **lst, t_list **lst_to_free);
int		ft_init_pipe(t_node *params);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/pipes/error.c                          */
/* -------------------------------------------------------------------------- */
void	ft_command_nt_found(char *cmd);
void	ft_putstr_fd(char *s, int fd);
void	ft_close(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/pipes/join.c                          */
/* -------------------------------------------------------------------------- */
char	*ft_strjoin_pimp(char *s1, char *s2);
int		ft_args(int ac, char **av);
int		ft_chk_cmd(char *cmd);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/pipes/utils_pipe.c                       */
/* -------------------------------------------------------------------------- */
void	ft_close_all(t_node *params);
int		ft_fork(t_node *params, t_list **lst, t_list **lst_to_free);
void	ft_dup2(int in, int out);
int		ft_cmp_heredoc(char **av, char *heredoc, t_node *params, int ac);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/pipes/utils_heredoc_2.c                     */
/* -------------------------------------------------------------------------- */
int		ft_hd_open(t_list **lst, int *j);
void	ft_hd_expand(char *limiter, char **line_ex, char *line, t_node *params);
void	ft_hd_quit_fork(t_node *params, t_list **lst_to_free);
int		ft_hd_writefile(t_list **lst, t_node *pars, t_list **lst_free, int *i);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/pipes/ft_split.c                        */
/* -------------------------------------------------------------------------- */
char	**ft_split(char const *s, char c);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/pipes/utils_both.c                       */
/* -------------------------------------------------------------------------- */
int		ft_init_pid(t_node *params);
int		ft_child_exec(t_node *params, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/pipes/ft_split_path.c                      */
/* -------------------------------------------------------------------------- */
char	**ft_split_path(char const *s, char c);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/pipes/utils_heredoc.c                      */
/* -------------------------------------------------------------------------- */
int		do_expandable(char *str);
void	ft_hd_free(char *line, char *line_after_expand);
int		ft_hd_write_fd(char *line, char *line_after_expand, int fd);
char	*ft_hd_create_name(char *str, int *j);
int		ft_hd_close(t_list **lst);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/pipes/heredoc.c                         */
/* -------------------------------------------------------------------------- */
int		ft_hd_write(t_list **lst, t_node *params, t_list **lst_to_free);
int		ft_hd_start(t_list **lst, t_node *params, t_list **lst_to_free);
int		ft_hd_write_node(t_list **lst, t_node *params, t_list **lst_to_free);
void	ft_hd_error(char *limiter);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/pipes/ft_get_output.c                      */
/* -------------------------------------------------------------------------- */
int		ft_get_output(t_list **lst, char **tab, int *k, int i);
int		ft_add_file_in(t_list **lst, int i, int *j, char **tab);
int		ft_get_input(t_list **lst, char **tab);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/utils_init.c                          */
/* -------------------------------------------------------------------------- */
void	ft_init_node(t_node *params);
int		ft_init_env(char **env, t_node *params);
int		ft_start(t_node *params, t_token *token, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/parsing/count_token.c                      */
/* -------------------------------------------------------------------------- */
int		ft_isspace(char c);
int		is_operator(char c);
void	ft_token_count(char *cmd, int *i, int *total);
int		ft_is_quote(char c);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/parsing/ft_unquoting.c                     */
/* -------------------------------------------------------------------------- */
char	*ft_strtrim_quoted(t_token *token, char *str, char *set);
char	*ft_unquoting(char *str);
int		ft_total_unquote(t_list **lst);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/parsing/token_check.c                      */
/* -------------------------------------------------------------------------- */
int		ft_main_check(char **token);
int		ft_check_quote(char *token);
int		ft_is_operator(char *token);
int		ft_check_token(t_token *token);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/parsing/utils_token_check.c                   */
/* -------------------------------------------------------------------------- */
int		ft_is_redire(char *token);
int		ft_check_next(t_token *token, int i);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/parsing/count_token_2.c                     */
/* -------------------------------------------------------------------------- */
int		ft_total_token(char *cmd);
void	ft_refact_incr(int *i, int *j, int new_j);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/parsing/parse_token_2.c                     */
/* -------------------------------------------------------------------------- */
int		ft_pass_sub_token(char **token, char *cmd, int *new_j, int *j);
void	ft_error_mess(char *token);
int		ft_sub_token(char **dest, char *cmd, int *j, int new_j);
int		ft_parse_tokens(t_token *token, char *cmd, int flag);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/parsing/parse_token.c                      */
/* -------------------------------------------------------------------------- */
int		ft_init_n_malloc(t_token *token, char *cmd, int *i, int *j);
void	ft_pass_quote(char *cmd, int *j);
int		ft_dup_token(t_token *token, char *cmd, int *i, int *j);
void	ft_pass_space(char *cmd, int *j);
int		ft_get_operator(t_token *token, char *cmd, int *i, int *j);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/exit/exit.c                           */
/* -------------------------------------------------------------------------- */
void	ft_free_params_2(t_node *params, int flag);
void	ft_free_params(t_node *params, int flag);
void	ft_free_list(t_list **start);
void	ft_hd_exit(t_node *params, t_list **start, int value);
void	ft_exit(t_node *params, t_list **start, int value);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/exit/exit_2.c                          */
/* -------------------------------------------------------------------------- */
void	ft_free_infile(t_list *tmp);
void	ft_free_outfile(t_list *tmp);
void	ft_free_lst(t_list **start);
void	ft_free_after_cmd(t_node *params, t_list **start, int flag);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils_print.c                          */
/* -------------------------------------------------------------------------- */
void	ft_print_lst(t_list *lst);
void	ft_print_tab(char **tokens);
void	ft_print_env(char **env);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/exec/utils_split_space.c                    */
/* -------------------------------------------------------------------------- */
int		ft_count(char *cmd);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/exec/ft_echo.c                         */
/* -------------------------------------------------------------------------- */
int		is_args(char *cmd);
void	ft_echo(char **cmd);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/exec/main_exec.c                        */
/* -------------------------------------------------------------------------- */
int		ft_count_binaries(t_list **lst);
int		ft_main_exec(t_node *params, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/exec/open_io_utils.c                      */
/* -------------------------------------------------------------------------- */
void	ft_print_io_error_choice(char *str, t_node *params, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/exec/is_builtin.c                        */
/* -------------------------------------------------------------------------- */
void	ft_exit_choice(t_node *params, t_list **start, char *args);
int		ft_is_builtin(char *cmd);
void	ft_cd_many_args_check(char **cmd, t_node *params);
int		ft_exec_builtin(t_node *params, char **cmd, t_list **lst_to_free);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/exec/exec_utils.c                        */
/* -------------------------------------------------------------------------- */
int		ft_prepare_cmd(t_list **lst);
int		ft_execute_one_builtin(t_node *params, t_list **lst);
int		ft_execute_one_binaries(t_node *params, t_list **lst);
int		ft_exec_one(t_node *params, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/exec/insert_file.c                       */
/* -------------------------------------------------------------------------- */
int		ft_save_file(t_list **lst);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/exec/create_list.c                       */
/* -------------------------------------------------------------------------- */
t_list	*init_lst(t_token *token);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/exec/open_io.c                         */
/* -------------------------------------------------------------------------- */
int		ft_open_io(t_list **lst, t_node *params, t_list **lst_to_free);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/exec/clean_redirection.c                    */
/* -------------------------------------------------------------------------- */
int		is_redirect(t_list **lst, int *i);
char	**ft_clean_redirection(t_list **lst);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/exec/utils_io.c                         */
/* -------------------------------------------------------------------------- */
void	ft_count_in(char **token, t_list **lst);
void	ft_count_out(char **token, t_list **lst);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/exec/ft_split_space.c                      */
/* -------------------------------------------------------------------------- */
char	**ft_split_space(char *cmd);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/exec/ft_get_output.c                      */
/* -------------------------------------------------------------------------- */
int		ft_get_output(t_list **lst, char **tab, int *k, int i);
int		ft_add_file_in(t_list **lst, int i, int *j, char **tab);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/expand/expand_utils.c                      */
/* -------------------------------------------------------------------------- */
int		ft_find_len_env(char *str);
char	*ft_strjoin_expand(char *token, char **env);
int		ft_expand_utils(char **ret, int *i);
int		ft_expand_utils_2(char **ret, char *token, int *i, t_node *p);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/expand/expand_utils_2.c                     */
/* -------------------------------------------------------------------------- */
void	ft_quoted_expand(t_token *token, char c);
int		ft_quote_expand(t_token *token, char **ret, t_node *params, char *cmd);
int		ft_count_dollar(char *cmd);
int		ft_no_dollars(int flag, char **ret, char *cmd);
int		ft_init_expand(int	*i, int *flag, char *cmd, t_token *token);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/expand/env_expand.c                       */
/* -------------------------------------------------------------------------- */
int		ft_expand_1(char **ret, char *token, t_node *par);
int		ft_verif_dollars(char **ret, char *cmd, t_node *params);
char	**ft_expand(t_token *token, t_node *params);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/env/utils_export.c                       */
/* -------------------------------------------------------------------------- */
int		ft_need_cat(char *var);
int		ft_size_s2(char *var);
char	*ft_dup_addon(char *var);
int		ft_cat_var(char **env, char *var, int j);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/env/utils_backslash.c                      */
/* -------------------------------------------------------------------------- */
int		ft_theres_backslash(char *token);
int		ft_nb_bs(char *token);
char	*ft_backslash(char *token);
int		ft_var_len(char *var);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/env/unset.c                           */
/* -------------------------------------------------------------------------- */
int		ft_is_in(char **var_lst, char *var);
int		ft_vld_unset(char *var);
int		ft_need(char **env, char **var_lst);
char	**ft_unset(char **env, char **var);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/env/export_3.c                         */
/* -------------------------------------------------------------------------- */
int		ft_theres_dquotes(char *token);
char	*ft_quote(char *token);
int		ft_need_unquote(char *var);
char	*ft_simple_unquote(char *var);
int		ft_export(t_node *params, char *token);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/env/utils_export_2.c                      */
/* -------------------------------------------------------------------------- */
char	*ft_second_cat(char *envi, char *addon);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/env/utils_error.c                        */
/* -------------------------------------------------------------------------- */
int		ft_strlen_exp(char *s);
int		ft_strcmp_exp(char *s1, char *s2);
int		ft_is_charset(char cara, char *charset);
int		ft_vld(char *var);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/env/export_2.c                         */
/* -------------------------------------------------------------------------- */
int		ft_check_equal(char *token);
char	*ft_unquote(char **tmp, int index);
char	**ft_add_var(char *var, char **env);
int		ft_find_occ(char **env, char *var);
int		ft_change_var(char **env, char *var, int j);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/env/export.c                          */
/* -------------------------------------------------------------------------- */
int		ft_find_occurence(char **env, char *cmd);
int		ft_find_index(char **export, int size);
int		ft_export_alph(char **env);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/dir/dir_prompt.c                        */
/* -------------------------------------------------------------------------- */
int		ft_get_last_word(char *str, int len);
char	*ft_get_last_dir(char *str);
char	*ft_cat_path(char *var, char *path);
int		ft_change_dir(t_node *params, char *path);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/dir/dir_error.c                         */
/* -------------------------------------------------------------------------- */
void	directory_error(char *str);
int		is_directory(char *str);

#endif
