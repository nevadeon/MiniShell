#ifndef FORWARD_H
# define FORWARD_H

# define IN 1
# define OUT 0

typedef enum e_shell_error		t_shell_error;
typedef enum e_token_type		t_token_type;
typedef enum e_redir_type		t_redir_type;
typedef enum e_ope_type			t_ope_type;

typedef struct s_list			t_list;
typedef struct s_str_list		t_str_list;
typedef struct s_redir_list		t_redir_list;
typedef struct s_ast			t_ast;
typedef struct s_token			t_token;
typedef struct s_token_list		t_token_list;
typedef struct s_ast_context	t_ast_context;
typedef struct s_ctx			t_ctx;
typedef struct s_redir_fds		t_redir_data;

#endif
