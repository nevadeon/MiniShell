#ifndef AST_H
# define AST_H

# include "forward.h"
# include "parsing.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "allocators/allocator.h"

typedef enum e_node_type
{
	NODE_LEAF,
	NODE_BRANCH,
}	t_node_type;

typedef enum e_ope_type
{
	OPE_PIPE,
}	t_ope_type;

typedef struct s_leaf
{
	t_str_list	*func;
	int			redir[2];
}	t_leaf;

typedef struct s_ope
{
	t_ope_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ope;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		t_leaf	leaf;
		t_ope	ope;
	};
}	t_ast;

typedef struct s_ast_context
{
	t_token_list	*tok_l;
	t_ast			*root;
	t_ast			*prev;
	t_ast			*prev_ope;
}	t_ast_context;

t_ast		*create_ast(t_ctx *ctx, t_ast_context *data);
void		print_ast(t_ast *ast, int indent);

#endif
