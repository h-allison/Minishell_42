/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbotel <cbotel@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:43:50 by cbotel            #+#    #+#             */
/*   Updated: 2025/07/04 16:41:19 by cbotel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFS_H
# define MS_DEFS_H

# include "ms_stdlibs.h"
# include "includes/libft.h"

extern bool	g_sig_in_prompt;

/* === COMMAND MACROS === */
# define IS_CD 1
# define IS_EXPORT 2
# define IS_ECHO 3
# define IS_ENV 4
# define IS_PWD 5
# define IS_UNSET 6
# define IS_EXIT 7

# define IS_PIPE 9
# define IS_OUTPUT_REDIRECT 10
# define IS_OUTPUT_APPEND 11
# define IS_INPUT_REDIRECT 12
# define IS_AND 13
# define IS_OR 14
# define IS_SUB 15

/* === SIGNAL SCOPES === */
# define SIGSCOPE_EXEC 0
# define SIGSCOPE_INTERACTIVE 1
# define SIGSCOPE_EXTERN 2
# define SIGSCOPE_HEREDOC 3

/* === PIPE & REDIRECT FDs === */
# define WRITE_END 1
# define READ_END 0

/* === COLOR CODES === */
# define RESET_COL "\033[0m"
# define GREEN     "\033[32m"
# define BLUE      "\033[94m"
# define YELLOW    "\033[33m"
# define CYAN      "\033[36m"
# define MAGENTA   "\033[35m"

/* === READLINE MACROS === */
# define RL_START_IGNORE "\001"
# define RL_END_IGNORE   "\002"

/* === GC STRUCT === */
typedef struct s_gc_mem
{
	void				*ptr_to_mem;
	size_t				size;
	struct s_gc_mem		*next;
	struct s_gc_mem		*tail;
}	t_gc_mem;

/* === ENUMS === */
typedef enum e_precedence
{
	PREC_HIGHEST,
	PREC_SUBSHELL,
	PREC_BACKGROUND,
	PREC_NOT,
	PREC_REDIRECT,
	PREC_PIPE,
	PREC_LOGIC,
	PREC_SEQUENCE
}	t_precedence;

typedef enum e_token_type
{
	T_ERROR,
	T_PIPE,
	T_OUTPUT,
	T_INPUT,
	T_APPEND,
	T_HEREDOC,
	T_ENV,
	T_WORD,
	T_OPEN_PAREN,
	T_CLOSE_PAREN,
	T_AND,
	T_OR,
	T_EOF,
	T_CMDSUB
}	t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_WORD,
	NODE_CMDSUB,
	NODE_PIPE,
	NODE_SEQUENCE,
	NODE_REDIRECT
}	t_node_type;

typedef enum e_input_status
{
	IN_INCOMPLETE = 0,
	IN_COMPLETE = 1,
	IN_ERROR = -1,
	IN_QUOTE_ERR = -2
}	t_input_status;

typedef enum e_ms_err
{
	ERR_MALLOC_FAIL,
	ERR_HEREDOC_INIT,
	ERR_INVALID_TOKEN,
	ERR_BACKGROUND,
	ERR_UNSUP_FEAT,
	ERR_CMD_NOT_FOUND,
	ERR_SYNTAX,
	ERR_OPEN_FAIL,
	ERR_EXEC_FAIL,
	ERR_TOO_MANY_ARGS,
	ERR_TOO_FEW_ARGS,
	ERR_UNKNOWN
}	t_ms_err;

/* === STRUCTS === */
typedef struct s_wordseg
{
	char				*text;
	bool				expand;
	struct s_wordseg	*next;
}	t_wordseg;

typedef struct s_token_state
{
	int		pos;
	int		start;
	bool	expand;
	char	quote_char;
	bool	in_quote;
}	t_token_state;

typedef struct s_token
{
	char			*value;
	size_t			len_value;
	t_token_type	type;
	t_precedence	prec;
	int				quoted;
	char			quote_char;
	bool			in_quote;
	bool			expand;
	struct s_shell	*shell;
	t_wordseg		*segs;
	bool			merge;
	int				start_index;
	int				line_num;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*target;
	t_token_type	type;
	bool			append;
	struct s_redir	*next;
}	t_redir;

typedef struct s_heredoc
{
	char				*delim;
	int					quotes;
	char				*path;
	struct s_heredoc	*next;
}	t_hdoc;

typedef struct s_node
{
	t_node_type			*type;
	char				*cmd;
	char				**args;
	struct s_node		*arglist;
	t_precedence		op_prec;
	int					quotes;
	int					arg_zero;
	t_redir				*redirections;
	bool				is_builtin;
	t_hdoc				*heredocs;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

typedef struct s_parse_state
{
	t_token	*start;
	t_token	*end;
	t_token	*op;
	t_token	*closing;
	t_node	*node;
}	t_parse_state;

typedef struct s_shell
{
	t_gc_mem		input_mem;
	t_gc_mem		parser_mem;
	t_gc_mem		exec_mem;

	char			*prompt;
	char			*buffer;
	t_input_status	in_status;
	char			*input;
	char			**envp;
	char			**export_list;
	char			**var_list;
	bool			end_of_file;
	t_token			*tokens;
	t_node			*ast;
	int				prev_read_fd;
	int				heredoc_counter;
	int				heredoc_fd;
	int				last_exit_code;
	char			protected_cwd[PATH_MAX + 1];
	bool			fatal;
}	t_shell;

#endif
