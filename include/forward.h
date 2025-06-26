#ifndef FORWARD_H
# define FORWARD_H

typedef enum e_token_type
{
	E_WORD,
	E_CONTROL_OPE,
	E_REDIR_OPE
}	t_token_type;

typedef enum e_redir_type
{
	E_REDIR_IN,
	E_REDIR_HEREDOC,
	E_REDIR_OUT_TRUNC,
	E_REDIR_OUT_APPEND,
	E_REDIR_LAST_INDEX
}	t_redir_type;

typedef enum e_ope_type
{
	E_OPE_PIPE,
	E_OPE_LAST_INDEX
}	t_ope_type;

typedef struct s_list			t_list;
typedef struct s_str_list		t_str_list;
typedef t_token_type			t_node_type;
typedef struct s_redir_list		t_redir_list;
typedef struct s_ast			t_ast;
typedef struct s_token			t_token;
typedef struct s_token_list		t_token_list;
typedef struct s_ast_context	t_ast_context;
typedef struct s_ctx			t_ctx;
typedef enum e_shell_error		t_shell_error;

#endif
