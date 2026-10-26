/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:08:31 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:39:51 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_H
# define MS_PARSING_H

# include "ms_defs.h"
# include "ms_core.h"

// heredoc.c
void	heredoc_start(t_shell *shell, t_node *node);
void	heredoc_init(t_shell *shell, t_hdoc *heredoc);
void	heredoc_add_to_node(t_shell *shell, t_node *node, \
										char *delim, int quoted);
void	heredoc_write_to_file(t_shell *shell, int fd, t_hdoc *heredoc);
void	heredoc_fork(t_shell *shell, t_hdoc *heredoc);
// heredoc_helpers.c
char	*heredoc_get_path(t_shell *shell);
void	heredoc_assemble_path(t_shell *shell, char *filename, \
										char **path, char *prefix);
char	*heredoc_remove_outer_quotes(t_shell *shell, char *str, int quotes);
void	heredoc_unlink_all(t_node *node);
// parse_merge.c
void	parse_fill_args(t_shell *shell, t_node *node, t_parse_state *state);
char	*parse_merge_tokens(t_shell *shell, t_token **curr, t_token *end);
int		parse_calc_merged_len(t_token *start, t_token *end);
// parse_ops_paren.c
void	parse_set_operator(t_token *curr, t_token **best, t_precedence *prec);
t_node	*parse_subshell(t_shell *shell, t_parse_state *state);
t_token	*parse_skip_paren(t_token *curr, t_token *end);
t_token	*parse_find_matching_paren(t_parse_state *state);
// parse_parsing.c
t_node	*parse_tokens(t_shell *shell, t_token *start, t_token *end);
t_token	*parse_handle_precedence(t_parse_state *state);
t_node	*parse_init_node(t_shell *shell);
void	parse_handle_operators(t_shell *shell, t_node *node, \
												t_parse_state *state);
void	parse_handle_commands(t_shell *shell, t_node *node, \
												t_parse_state *state);
// parse_redirections.c
void	parse_handle_redir(t_shell *shell, t_node *node, \
								t_token *curr, t_parse_state *state);
bool	parse_val_redir_token(t_shell *shell, t_token *curr, \
												t_parse_state *state);
void	parse_add_redir(t_shell *shell, t_node *node, \
						char *redir_target, t_token_type type);
void	parse_remove_redir_tokens(t_parse_state *state, t_token *redir);
void	parse_handle_heredoc(t_shell *shell, t_node *node, \
								t_token *curr, t_parse_state *state);

#endif
