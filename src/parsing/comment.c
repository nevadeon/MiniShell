/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:11 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_comment(t_alloc *alloc, char **input)
{
	size_t	index;
	size_t	comment_start;
	size_t	comment_end;

	index = 0;
	while ((*input)[index])
	{
		if ((*input)[index] == '#')
		{
			comment_start = index;
			while ((*input)[index] && (*input)[index] != '\n')
				index++;
			comment_end = index;
			str_replace(alloc, (t_replace){
				.str = input,
				.rep = "",
				.start = comment_start,
				.end = comment_end
			});
			index = comment_start;
			continue ;
		}
		index++;
	}
}
