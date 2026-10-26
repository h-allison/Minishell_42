/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:03:16 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:48:45 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_INPUT_H
# define MS_INPUT_H

# include "ms_core.h"
# include "ms_defs.h"
# include "ms_tokenizing.h"

// prompt_dir.c
char			*prompt_find_first_dir(t_shell *shell, const char *str);
char			*prompt_find_last_dir(char *str);
bool			prompt_path_has_home(char *str);
char			*prompt_cwd(t_shell *shell);
char			*prompt_alt(t_shell *shell);
// prompt_formatting.c
char			*prompt_colorize(t_shell *shell, \
									const char *color, const char *str);
char			*prompt_shorten_cwd(t_shell *shell, char *str, int	*level);
char			*prompt_shorten_home(t_shell *shell, char *last, int level);
char			*prompt_shorten_path(t_shell *shell, char *first, char *last);
char			*prompt_name(t_shell *shell);
//prompt_user_host.c
char			*prompt_user(t_shell *shell);
char			*prompt_host(t_shell *shell);
char			*prompt_read_hostname_file(t_shell *shell, const char *path);
char			*prompt_append(t_shell *shell, char *buffer, \
									char *module, t_gc_mem *mem);
void			prompt_update(t_shell *shell);
// in_input.c
void			in_input_loop(t_shell *shell);
void			in_get_input(t_shell *shell);
void			in_append_input(t_shell *shell, char **buffer, char *line);
void			in_check_status(t_shell *shell);
//in_handling.c
void			in_handle_error(t_shell *shell);
t_input_status	in_handle_operator(char *buffer);
t_input_status	in_handle_separated_operators(const char *buffer);
// in_operators.c
t_input_status	in_run_all_checks(const char *buffer);
t_input_status	in_validate_operators(const char *buffer);
t_input_status	in_check_op_sequence(const char *buffer, int start, int end);
t_input_status	in_check_mixed_ops(const char *buffer, int start, int end);
t_input_status	in_check_op_rep(const char *buffer, int start, \
													int end, int op_rep);
// in_parentheses.c
t_input_status	in_check_parens(char *buffer);
void			in_handle_paren_char(char **buf_pt, int *depth);
t_input_status	in_handle_closing_paren(int *depth);
int				in_count_redirect_operators(const char *buffer);
t_input_status	in_check_trailing_operators(const char *buffer);
// in_quotes.c
t_input_status	in_check_quotes(char *buf);
void			in_process_quote_char(char c, bool *in_quotes, char *quote);
char			*in_skip_quote(char *buf_ptr);
t_input_status	in_check_single_amp(const char *buffer, int start, int op_rep);
// in_helpers.c
bool			in_is_invalid_combination(char first_op, char next_char);
void			in_print_operator_error(const char *buffer, int pos);
bool			in_ends_with_redirect(const char *buffer);

#endif
