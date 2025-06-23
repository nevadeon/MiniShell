#ifndef AST_H
# define AST_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "allocator.h"
# include "parsing.h"

typedef t_token_type	t_node_type;

typedef enum e_ope_type
{
	E_OPE_PIPE,
	E_OPE_LAST_INDEX
}	t_ope_type;

typedef struct s_redir_list
{
	struct s_redir_list	*next;
	char				*content;
	t_redir_type		type;
}	t_redir_list;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		struct
		{
			t_str_list		*func;
			t_redir_list	*redir_in;
			t_redir_list	*redir_out;
		}	s_leaf;
		struct
		{
			t_ope_type		type;
			struct s_ast	*left;
			struct s_ast	*right;
		}	s_ope;
	};
}	t_ast;

typedef struct s_ast_context
{
	t_token_list	*token_list_item;
	t_ast			*root;
	t_ast			*prev;
	t_ast			*prev_ope;
}	t_ast_context;

t_ast		*create_ast(t_alloc *alloc, t_ast_context *data);
void		print_ast(t_ast *ast, int indent);

#endif
