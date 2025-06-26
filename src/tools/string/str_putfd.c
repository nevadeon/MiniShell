/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_putfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:46:05 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"

size_t	str_putfd(const char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (str_putfd("(null)", fd));
	len = str_len(s);
	write(fd, s, len);
	return (len);
}
