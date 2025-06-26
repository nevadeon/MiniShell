/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_chr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:57 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"

char	*str_chr(const char *s, int c)
{
	assert(s);
	if (!s)
		return (NULL);
	while ((unsigned char) *s != (unsigned char) c && *s)
		s++;
	if ((unsigned char) *s == (unsigned char) c)
		return ((char *)s);
	return (NULL);
}
