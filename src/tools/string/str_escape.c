/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:46:00 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"

bool	str_escape(char *s, size_t *index, char start, char end)
{
	assert(s);
	if (!s[*index])
		return (true);
	if (s[*index] != start)
		return (true);
	(*index)++;
	while (s[*index] && s[*index] != end)
		(*index)++;
	if (s[*index] == end)
	{
		(*index)++;
		return (true);
	}
	return (false);
}
