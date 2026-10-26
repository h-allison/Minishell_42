/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:10:16 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:46:56 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOKENIZING_H
# define MS_TOKENIZING_H

# include "ms_defs.h"
# include "ms_core.h"

// tok_cmdsub.c
void			tok_handle_cmdsub(t_shell *shell, int *i, t_token *tok);
int				tok_find_cmdsub_end(t_shell *shell, int *i);
void			tok_create_cmdsub_value(t_token *tok, t_shell *shell, \
												int start, int end);
bool			tok_check_cmdsub_ahead(t_shell *shell, int start);
int				tok_validate_var_name(const char *input);
// tok_operators.c
void			tok_handle_operator(t_shell *shell, int *i, t_token *token);
void			tok_handle_pipe(t_shell *shell, int *i, t_token *token);
void			tok_handle_paren(t_shell *shell, int *i, t_token *token);
bool			tok_is_operator_start(char c);
// tok_quotes.c
bool			tok_handle_quoted_assign(t_shell *shell, int *i, t_token *tok);
int				tok_skip_quoted_segment(const char *input);
int				tok_skip_quote_content(const char *input, int start, \
													char quote);
bool			tok_handle_open_quote(t_shell *shell, t_token *tok, \
										t_token_state *tok_state);
bool			tok_handle_close_quote(t_shell *shell, t_token *tok, \
										t_token_state *tok_state);
// tok_redirect.c
void			tok_handle_redirect(t_shell *shell, int *i, t_token *token);
void			tok_add_append(t_shell *shell, int *i, t_token *token);
void			tok_add_heredoc(t_shell *shell, int *i, t_token *token);
void			tok_add_input(t_shell *shell, int *i, t_token *token);
void			tok_add_output(t_shell *shell, int *i, t_token *token);
// tok_segments.c
size_t			tok_calc_total_len(t_wordseg *seg);
void			tok_flatten_segments(t_token *token);
void			tok_append_token(t_shell *shell, t_token *token);
bool			tok_is_token_boundary(char c);
bool			tok_is_unclosed_boundary(char c);
// tok_tokenize.c
void			tok_tokenize(t_shell *shell);
t_token			*tok_init_token(t_shell *shell);
void			tok_handle_token_type(t_shell *shell, int *i, t_token *token);
t_precedence	tok_get_precedence(t_token_type type);
void			tok_init_state(t_token_state *state, int pos);
// tok_word.c
void			tok_handle_word(t_shell *shell, int *i, t_token *tok);
void			tok_process_word_loop(t_shell *shell, t_token *tok, \
													t_token_state *state);
void			tok_add_segment(t_token *token, char *start, \
													char *end, bool expand);
bool			tok_should_merge(char *input, int token_end, bool in_quote);
void			tok_finish_word(t_shell *shell, t_token *token);
// tok_expand.c
char			*tok_expand_vars(t_shell *shell, char *line);
char			*tok_expand_token(t_shell *shell, char *line, \
													char *result, int *i);
char			*tok_append_status(t_shell *shell, char *result, int *i);
char			*tok_append_var(t_shell *shell, char *base, char *add);
char			*tok_append_char(t_shell *shell, char *base, char c);
// tok_assign.c
void			tok_add_assignment_segments(t_shell *shell, t_token *tok, \
															int start, int len);
bool			tok_split_assign(t_shell *shell, int *i, t_token *tok);
int				tok_find_token_end(t_shell *shell, int start);
char			*tok_find_assignment_operator(t_shell *shell, \
												int start, int end);

#endif
