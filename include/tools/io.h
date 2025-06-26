/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:54:30 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:54:31 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include "tools/str.h"

# define DEC "0123456789"
# define HEX_LOW "0123456789abcdef"
# define HEX_UPP "0123456789ABCDEF"
# define STDERR 2

size_t	io_dprintf(int fd, const char *format, ...);
size_t	io_dputchar(int fd, char c);
size_t	io_dputstr(int fd, const char *s);
size_t	io_dputptr(int fd, void *p);
size_t	io_dputlbase(int fd, long n, char *base);
size_t	io_dputulbase(int fd, uint64_t ul, char *base);
void	io_dputendl(int fd, const char *s);
void	io_dputnbr(int fd, int n);
int		io_fopen(const char *pathname, int flags, ...);

#endif
