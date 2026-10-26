/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:44:54 by hallison          #+#    #+#             */
/*   Updated: 2025/06/23 16:44:55 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H

# include "ms_defs.h"
# include "ms_core.h"

/* BASIC EXEC */
int		start_exec(t_node *ast, char ***envp, t_shell *shell);
int		set_arg_zero_code(char *cmd);
int		handle_built_in(t_node *node, char ***envp, t_shell *shell);

/* PIPES & REDIRECTIONS */
int		open_pipe(t_node *ast, char ***envp, t_shell *shell);
int		exec_redir(t_node *node, char ***envp, t_shell *shell);
int		open_all_fds(t_node *node, int *file_fd);
int		open_all_for_input(t_node *node);
int		open_all_for_output(t_node *node);
int		redirect_output(t_node *ast, char ***envp, t_shell *shell);
int		redirect_input(t_node *node, char ***envp, t_shell *shell);
int		dup_original_fds(int *original_stdin, int *original_stdout);
int		replace_stdin_stdout(int in_file_fd, int out_file_fd);
int		restore_stdin_stdout(int original_in, int original_out);
int		close_fd_dups(t_shell *shell, int fd_1, int fd_2);
int		exec_redir_exit(t_node *node, t_shell *shell);

/* ENV, EXPORT & UNSET */
int		exec_export(t_shell *shell, t_node *node, char ***envp);
int		exec_env(t_node *node, char **envp);
int		exec_unset(t_shell *shell, t_node *node, char ***envp);
int		print_export_list(t_shell *shell, char **export_list, char **envp);
int		realloc_and_add_var_to_envp(t_shell *shell, char *var, char ***envp);
int		update_var(char *var, char ***envp);
void	print_export_alphabetical(t_shell *shell, char **print_list, int len);
int		export_var_no_assign(t_shell *shl, char *var, char ***lst, char **envp);
int		auto_export(t_shell *shell, char *var, char ***envp);
void	free_envp(char **envp);
int		realloc_and_del_1_envp(t_shell *shell, char ***envp, int delete_i);
int		find_export_i(char *var, char **export_list);
int		find_env_index_2(char *var, char **envp);
int		get_var_len(char *full_var_string);

/* CD */
int		exec_cd(t_shell *shell, t_node *node, char ***envp);
int		change_directory(char *path);
int		update_pwd_and_old_pwd(t_shell *shell, char ***envp);

/* ECHO */
int		exec_echo(t_node *node);

/* PWD */
int		exec_pwd(t_shell *shell);

/* EXTERNAL*/
int		handle_external(t_shell *shell, t_node *node, char **envp);
char	*get_path(t_shell *shell, char *command, char **envp);

/* UTILITIES */
int		is_directory(char *pathname);
int		ft_isnumber(const char *str);
bool	is_a_path(char *path);
int		free_arguments(char **arguments);
void	free_list_on_error(char **print_list, int j);
int		init_heredoc(void);

/* EXECUTION ERROR HANDLING */
int		ms_error_cmd_not_found(t_shell *shell, char *s);
int		ms_error_no_such_file(t_shell *shell, char *s);
int		ms_error_fail(t_shell *shell, int code, char *ft, char *call);
int		ms_error_dot_sourcing(void);
int		ms_error_syntax(int code, char *s);
int		ms_error_s(int code, char *s);
int		ms_error_cd(int code, char *s);
int		ms_error_export(t_shell *shell, int code, char *s);
int		ms_error_exit(t_shell *shell, int code, char *s);
int		ms_error_redirect(char *s);
int		ms_error_external(int code, int why, char *s);

#endif
