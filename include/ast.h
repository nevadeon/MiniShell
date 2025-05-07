#ifndef AST_H
# define AST_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list	t_list;

typedef struct s_strlist
{
	struct s_strlist	*next;
	char				*content;
}	t_strlist;

typedef struct s_dir
{
	int		nb_dir;
	t_list	*head;
}	t_dir;

typedef enum e_leaf_type
{
	E_LEAF_FUNC,
	E_LEAF_FILENAME,
	E_LEAF_LAST_INDEX
}	t_leaf_type;

typedef enum e_node_type
{
	E_NODE_OPE,
	E_NODE_LEAF,
	E_NODE_LAST_INDEX
}	t_node_type;

typedef enum e_ope_type
{
	E_OPE_PIPE,
	E_OPE_LAST_INDEX
}	t_ope_type;

typedef enum e_redir_type
{
	E_REDIR_IN,          // <
	E_REDIR_HEREDOC,     // <<
	E_REDIR_OUT_TRUNC,   // >
	E_REDIR_OUT_APPEND,  // >>
	E_REDIR_LAST_INDEX
}	t_redir_type;

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
			t_strlist		*args;
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

typedef struct s_ast_data
{
	char	*input;
	t_ast	*prev;
	t_ast	*root;
	t_ast	*last_ope;
}	t_ast_data;

t_ast_data	*init_ast_data(char *input);
t_ast		*create_ast(t_ast_data *data);
t_ast		*create_ast_by_hand(void);
t_ast		*handle_ope(t_ast_data *data, char *word);
t_ast		*handle_leaf(t_ast_data *data, char *word);
char		*get_next_word(char **input);
void		print_ast(t_ast *ast, int indent);

#endif
