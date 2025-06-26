/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:25 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include "minishell.h"

static char	*_get_git_head(void)
{
	static char	buffer[PATH_MAX];
	int			fd;
	int			b_read;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd == -1)
		return (NULL);
	b_read = read(fd, buffer, PATH_MAX - 1);
	buffer[b_read - 1] = '\0';
	close(fd);
	if (b_read <= 0)
		return (NULL);
	while (b_read)
	{
		if (buffer[b_read] == '/')
			return (&buffer[b_read + 1]);
		b_read--;
	}
	return (NULL);
}

static const char	*g_prefix = GREEN"minishell "PURPLE;
static const char	*g_mid = GREEN" git:("BROWN;
static const char	*g_suffix = GREEN")# "RESET;
static const char	*g_suffix2 = GREEN"# "RESET;

char	*readline_prompt(t_alloc *alloc)
{
	char	cwd[PATH_MAX];
	char	*git_head;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	git_head = _get_git_head();
	if (git_head)
		return (str_vjoin(alloc, 5, g_prefix, cwd, g_mid, git_head, g_suffix));
	return (str_vjoin(alloc, 3, g_prefix, cwd, g_suffix2));
}
