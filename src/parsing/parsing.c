#include "allocator.h"
#include "parsing.h"
#include "stdio.h"

t_ast	*parsing(t_alloc *alloc, char **inp)
{
	t_token_list	*token_list;
	t_ast_context	data;
	t_ast			*ast;

	errno = 0;
	remove_comment(alloc, inp);
	token_list = tokenize(alloc, inp);
	tilde_expanding(alloc, token_list);
	var_expanding(alloc, token_list);
	if (errno)
		return (NULL);
	word_splitting(alloc, token_list);
	wildcard_expanding(alloc, token_list);
	quote_removal(alloc, token_list);

	data.token_list_item = token_list;
	data.root = NULL;
	data.prev = NULL;
	data.prev_ope = NULL;
	ast = create_ast(alloc, &data);
	return (ast);
}

/*
 * lecture / commentaires
 * tokenisation (coupure en mots / opérateurs) -> alias performed ici (bonus ?)
 * brace expansion {draft, final}.txt en draft.txt, final.txt (bonus ?)
 * tilde expansion : ~/Downloads en /home/user/Download et ~otheruser en /home/otheruser
 * variable expansion (pas dans les simples quotes)
 * word splitting selon $IFS (pas sur variables doubles quotees)
 * wildcards
 * quote removal
 * executing avec redir
*/