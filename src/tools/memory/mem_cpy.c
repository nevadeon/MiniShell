/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:54:15 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:54:16 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/memory.h"

void	*mem_cpy(void *dest, const void *src, size_t n)
{
	const uint8_t	*s;
	uint8_t			*d;

	if (n != 0 && (dest == src))
		return (dest);
	s = (const uint8_t *)src;
	d = (uint8_t *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}
