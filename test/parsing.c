#include "test.h"

void	test_comment(t_ctx *ctx)
{
	char	*input;

	input = str_dup(*ctx->cmd, "echo a#REMOOVE");
	remove_comment(*ctx->cmd, &input);
	assert(str_equals(input, "echo a"));

	input = str_dup(*ctx->cmd, "echo a#REMOOVE\nnot remove");
	remove_comment(*ctx->cmd, &input);
	assert(str_equals(input, "echo a\nnot remove"));

}

void	test_tokenize(t_ctx *ctx)
{
	char			*input;
	t_token_list	*token_list;
	t_token_list	*current;

	// Test basic tokenization with redirections and quotes
	input = str_dup(*ctx->cmd, "cmd >> \">>\" << < 'cmd '");
	token_list = tokenize(ctx, &input);
	assert(token_list);
	assert(token_list->content->type == E_WORD);
	assert(str_equals(token_list->content->str, "cmd"));
	
	current = token_list->next;
	assert(current && current->content->type == E_REDIR_OPE);
	assert(str_equals(current->content->str, ">>"));
	
	current = current->next;
	assert(current && current->content->type == E_WORD);
	assert(str_equals(current->content->str, "\">>\""));
	
	current = current->next;
	assert(current && current->content->type == E_REDIR_OPE);
	assert(str_equals(current->content->str, "<<"));
	
	current = current->next;
	assert(current && current->content->type == E_REDIR_OPE);
	assert(str_equals(current->content->str, "<"));
	
	current = current->next;
	assert(current && current->content->type == E_WORD);
	assert(str_equals(current->content->str, "'cmd '"));
}

void	test_tokenize_pipes(t_ctx *ctx)
{
	char			*input;
	t_token_list	*token_list;
	t_token_list	*current;

	input = str_dup(*ctx->cmd, "ls -la | grep test | wc -l");
	token_list = tokenize(ctx, &input);
	assert(token_list);
	
	// First command
	assert(token_list->content->type == E_WORD);
	assert(str_equals(token_list->content->str, "ls"));
	
	current = token_list->next;
	assert(current && current->content->type == E_WORD);
	assert(str_equals(current->content->str, "-la"));
	
	// First pipe
	current = current->next;
	assert(current && current->content->type == E_CONTROL_OPE);
	assert(str_equals(current->content->str, "|"));
	
	// Second command
	current = current->next;
	assert(current && current->content->type == E_WORD);
	assert(str_equals(current->content->str, "grep"));
}

void	test_tokenize_quotes(t_ctx *ctx)
{
	char			*input;
	t_token_list	*token_list;

	// Test single quotes
	input = str_dup(*ctx->cmd, "echo 'hello world'");
	token_list = tokenize(ctx, &input);
	assert(token_list);
	assert(token_list->next && token_list->next->content->type == E_WORD);
	assert(str_equals(token_list->next->content->str, "'hello world'"));

	// Test double quotes with variables
	input = str_dup(*ctx->cmd, "echo \"hello $USER\"");
	token_list = tokenize(ctx, &input);
	assert(token_list);
	assert(token_list->next && token_list->next->content->type == E_WORD);
}

void	test_tokenize_edge_cases(t_ctx *ctx)
{
	char			*input;
	t_token_list	*token_list;

	// Empty input
	input = str_dup(*ctx->cmd, "");
	token_list = tokenize(ctx, &input);
	assert(token_list == NULL);

	// Only whitespace
	input = str_dup(*ctx->cmd, "   \t  \n  ");
	token_list = tokenize(ctx, &input);
	assert(token_list == NULL);

	// Multiple redirections
	input = str_dup(*ctx->cmd, "cmd > file >> append < input");
	token_list = tokenize(ctx, &input);
	assert(token_list);
	assert(token_list->content->type == E_WORD);
}

void	test_tilde_expanding(t_ctx *ctx)
{
	char			*input;
	t_token_list	*token_list;

	// Test basic tilde expansion (~)
	input = str_dup(*ctx->cmd, "echo ~");
	token_list = tokenize(ctx, &input);
	tilde_expanding(ctx, token_list);
	assert(token_list->next && token_list->next->content->type == E_WORD);
	// Should expand to HOME environment variable
	assert(token_list->next->content->str[0] == '/');

	// Test tilde with path (~/repo)
	input = str_dup(*ctx->cmd, "cd ~/repo");
	token_list = tokenize(ctx, &input);
	tilde_expanding(ctx, token_list);
	assert(token_list->next && token_list->next->content->type == E_WORD);
	// Should start with / and end with /repo
	assert(token_list->next->content->str[0] == '/');
	assert(str_contains(token_list->next->content->str, "/repo"));

	// Test tilde with username (~user)
	input = str_dup(*ctx->cmd, "ls ~root");
	token_list = tokenize(ctx, &input);
	tilde_expanding(ctx, token_list);
	assert(token_list->next && token_list->next->content->type == E_WORD);
	// Should expand to user's home directory
	assert(token_list->next->content->str[0] == '/');

	// Test no tilde (should remain unchanged)
	input = str_dup(*ctx->cmd, "echo hello");
	token_list = tokenize(ctx, &input);
	tilde_expanding(ctx, token_list);
	assert(token_list->next && token_list->next->content->type == E_WORD);
	assert(str_equals(token_list->next->content->str, "hello"));
}

void	test_parsing(char ***envp)
{
	t_alloc	*alloc_test;
	t_ctx	*ctx;

	alloc_test = new_malloc_allocator(ARENA_BLOCK_SIZE);
	ctx = mem_alloc(alloc_test, sizeof(t_ctx));
	*ctx = (t_ctx){
		.prog = &alloc_test,
		.cmd = &alloc_test,
		.env = envp,
		.last_error_type = ERR_NONE,
		.last_exit_code = 0,
	};

	printf("Running parsing tests...\n");
	test_comment(ctx);
	printf("✓ Comment tests passed\n");

	test_tokenize(ctx);
	printf("✓ Basic tokenize tests passed\n");

	test_tokenize_pipes(ctx);
	printf("✓ Pipe tokenize tests passed\n");

	test_tokenize_quotes(ctx);
	printf("✓ Quote tokenize tests passed\n");

	test_tokenize_edge_cases(ctx);
	printf("✓ Edge case tests passed\n");

	test_tilde_expanding(ctx);
	printf("✓ Tilde expanding tests passed\n");
	printf("All parsing tests passed!\n");
	free_allocator(ctx->cmd);
}
