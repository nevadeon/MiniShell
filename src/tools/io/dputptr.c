/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dputptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:53:01 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:53:01 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/io.h"

size_t	io_dputptr(int fd, void *p)
{
	if (p == NULL)
		return (io_dputstr(fd, "(nil)"));
	io_dputstr(fd, "0x");
	return (io_dputulbase(fd, (size_t) p, HEX_LOW) + 2);
}
