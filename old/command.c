#include "ast.h"
#include "parsing.h"
#include "executing.h"

static t_ast_context	*_init_ast_context(t_alloc *alloc, char *input)
{
	t_ast_context	*ast_context;

	ast_context = mem_alloc(alloc, 1 * sizeof(t_ast_context));
	ast_context->alloc = alloc;
	ast_context->input = input;
	ast_context->last_ope = NULL;
	ast_context->prev_token = E_TOKEN_INIT;
	ast_context->prev = NULL;
	ast_context->root = NULL;
	return (ast_context);
}

char	*get_next_word(t_alloc *alloc, char **input)
{
	size_t	word_l;
	char	*word;

	word_l = 0;
	while ((*input)[word_l] == ' ')
		(*input)++;
	if (is_a_token((*input)[word_l]))
		return ()
	while (!is_a_token((*input)[word_l]))
	{
		str_escape((*input), &word_l, '"', '"');
		str_escape((*input), &word_l, '\'', '\'');
		word_l++;
	}
	word = str_extract(alloc, (*input), 0, word_l + 1);
	word[word_l] = '\0';
	(*input) += word_l;
	return (word);
}

void	handle_command(t_alloc **alloc_prog, t_alloc **alloc_cmd, char *input)
{
	t_ast_context		*data;
	t_ast				*ast;

	expand(*alloc_cmd, &input);
	printf("%s\n", input);
	data = _init_ast_context(*alloc_cmd, input);
	ast = create_ast(data);
	if (!ast)
		return ;
	print_ast(ast, 0);
	execute_ast(alloc_prog, alloc_cmd, ast);
}
