/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dputnbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:52:58 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:52:59 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/io.h"

static void	_recursive(int fd, long l)
{
	if (l >= 10)
		_recursive(fd, l / 10);
	io_dputchar(fd, l % 10 + '0');
}

void	io_dputnbr(int fd, int n)
{
	long	l;

	l = (long) n;
	if (l < 0)
	{
		io_dputchar(fd, '-');
		l = -l;
	}
	_recursive(fd, l);
}
