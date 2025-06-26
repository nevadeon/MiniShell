/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:16 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocators/allocator.h"
#include "minishell.h"
#include "parsing.h"
#include "stdio.h"

t_token_list	*parsing(t_ctx *ctx, char *inp)
{
	t_token_list	*token_list;

	if (!inp || inp[0] == '\0')
		return (NULL);
	remove_comment(*ctx->cmd, &inp);
	token_list = tokenize(ctx, &inp);
	if (ctx->last_error_type)
		return (NULL);
	tilde_expanding(ctx, token_list);
	var_expanding(ctx, token_list);
	if (ctx->last_error_type)
		return (NULL);
	word_splitting(ctx, token_list);
	wildcard_expanding(*ctx->cmd, token_list);
	quote_removal(*ctx->cmd, token_list);
	if (ctx->last_error_type)
		return (NULL);
	return (token_list);
}

/*
 * lecture / commentaires
 * tokenisation (coupure en mots / opérateurs) -> alias performed ici (bonus ?)
 * brace expansion {draft, final}.txt en draft.txt, final.txt (bonus ?)
 * tilde expansion : ~/Downloads en /home/user/Download et ~otheruser en
 * /home/otheruser
 * variable expansion (pas dans les simples quotes)
 * word splitting selon $IFS (pas sur variables doubles quotees)
 * wildcards
 * quote removal
 * executing avec redir
*/
