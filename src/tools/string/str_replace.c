/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:46:08 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"

/*
* @return the len added to the string (can be negative)
*/
int	str_replace(t_alloc *alloc, t_replace d)
{
	char	*old_str;
	char	*new_word;
	size_t	str_l;
	size_t	rep_l;
	size_t	new_word_l;

	old_str = *d.str;
	rep_l = str_len(d.rep);
	str_l = str_len(old_str);
	new_word_l = str_l - (d.end - d.start) + rep_l;
	new_word = mem_alloc(alloc, (new_word_l + 1) * sizeof(char));
	assert(new_word);
	str_memcpy(new_word, old_str, d.start);
	str_memcpy(new_word + d.start, d.rep, rep_l);
	str_memcpy(new_word + d.start + rep_l, old_str + d.end, str_l - d.end);
	new_word[new_word_l] = '\0';
	*d.str = NULL;
	*d.str = new_word;
	return (new_word_l - str_l);
}
