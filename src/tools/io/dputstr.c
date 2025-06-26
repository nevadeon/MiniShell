/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dputstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:53:03 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:53:03 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/io.h"

size_t	io_dputstr(int fd, const char *s)
{
	size_t	len;

	if (s == NULL)
		return (io_dputstr(fd, "(null)"));
	len = str_len(s);
	write(fd, s, len);
	return (len);
}
