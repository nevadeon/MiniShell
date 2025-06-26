/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pid_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:02 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

t_pid_list	*lst_pid_new(t_alloc *alloc, pid_t pid)
{
	t_pid_list	*new_node;

	new_node = mem_alloc(alloc, sizeof(t_pid_list));
	if (!new_node)
		return (NULL);
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}
