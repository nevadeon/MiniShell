#ifndef AST_H
# define AST_H

# include "forward.h"
# include "parsing.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "allocators/allocator.h"

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

t_ast		*create_ast(t_ctx *ctx, t_ast_context *data);
void		print_ast(t_ast *ast, int indent);

#endif
