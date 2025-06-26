/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:08 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/list.h"
#include "parsing.h"
#include <string.h>

static void	plstr(void *content)
{
	printf("%s", (char *)content);
}

static void	predir(t_ast *ast)
{
	t_redir_list	*current;

	current = ast->leaf.redir_list;
	while (current)
	{
		switch (current->type)
		{
			case REDIR_HEREDOC: printf(", HDOC: %d", current->heredoc); break;
			case REDIR_IN: printf(", < %s", current->filename); break;
			case REDIR_OUT_TRUNC: printf(", > %s", current->filename); break;
			case REDIR_OUT_APPEND: printf(", >> %s", current->filename); break;
			default : assert(false);
		}
		current = current->next;
	}
}

static void	_print_leaf(t_ast *ast)
{
	if (!ast->leaf.func)
		return ;
	printf("function : %s", ast->leaf.func->content);
	if (ast->leaf.func->next)
	{
		printf(" [");
		lst_print((t_list *)ast->leaf.func->next, (void (*)(void *))plstr);
		printf("]");
	}
	predir(ast);
	printf("\n");
}

void	print_ast(t_ast *ast, int indent)
{
	int	i;

	if (!ast)
		return ;
	i = -1;
	while (++i < indent)
		printf("  ");
	if (ast->type == NODE_LEAF)
		_print_leaf(ast);
	else if (ast->type == NODE_BRANCH)
	{
		printf("Operator: |\n");
		print_ast(ast->ope.left, indent + 1);
		print_ast(ast->ope.right, indent + 1);
	}
}
