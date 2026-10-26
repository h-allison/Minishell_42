/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:27:03 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:20:45 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_CORE_H
# define MS_CORE_H

# include "ms_defs.h"

/* === main & init === */
int		main(int argc, char **argv, char **envp);
int		ms_start_minishell(t_shell *shell);
// ms_init.c
void	copy_envp(char **original_envp, t_shell *shell);
char	**init_export_list(t_shell *shell);
void	increment_shell_level(t_shell *shell, char ***envp);
void	ms_init_shell(char **envp, t_shell *shell);
void	ms_reset_shell_state(t_shell *shell);

/* === GC & exit === */
// ms_exit.c
int		ms_exit(t_shell *shell, t_node *node);
int		ms_clean_exit(t_shell *shell, int exit_code, bool print);
int		print_last_exit(t_shell *shell); // check if func is needed
bool	ft_is_valid_int_range(char *str);
// ms_garbage.c
void	*gc_malloc(t_shell *shell, size_t size, t_gc_mem *mem);
void	gc_free(void *ptr, t_gc_mem *mem);
void	gc_cleanup(t_gc_mem *mem);
void	gc_cleanup_shell(t_shell *shell);
void	gc_init(t_gc_mem *arena);

/* === signals === */
void	sig_set_scope(t_shell *shell, int type);
void	sig_handle_prompt(int signum);
void	sig_handle_heredoc(int signum);
void	sig_exit_error(t_shell *shell, int code);

// ms_helper_functions.c
bool	ft_isspace(char c);
bool	ft_is_escaped(const char *input, int pos);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isnumber(const char *str);
char	*ft_strcpy(char *dst, const char *src);

// ms_utilities.c
int		find_env_index(char *var, int match_len, char **envp);
int		find_env_index_2(char *var, char **envp);
char	*get_str_from_envp(char *var_name, char **envp);
char	*gc_strdup(t_shell *shell, const char *src, t_gc_mem *mem);

/* === errors === */
// ms_handle_errors.c
char	*ms_get_error_msg(t_ms_err err);
void	ms_error_msg(t_shell *shell, int code, \
						const char *spot, t_ms_err err);

#endif
