/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:35 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/list.h"

int	lst_len(t_list *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}
