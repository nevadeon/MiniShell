/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:01 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	dup_close(int source_fd, int dest_fd)
{
	dup2(source_fd, dest_fd);
	close(source_fd);
}
