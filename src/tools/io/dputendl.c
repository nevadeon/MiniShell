/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dputendl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:52:54 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:52:54 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/io.h"

void	io_dputendl(int fd, const char *s)
{
	size_t	len;

	len = str_len(s);
	write(fd, s, len);
	io_dputchar(fd, '\n');
}
