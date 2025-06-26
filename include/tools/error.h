/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:50 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 16:01:58 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "stdio.h"

typedef struct s_error_category
{
	const char	*(*name)(void);
	const char	*(*message)(int error);
}	t_error_category;

typedef struct s_error_code
{
	int						value;
	const t_error_category	*error_category;
}	t_error_code;

t_error_code	make_error(int val, const t_error_category *cat);

const char		*error_name(const t_error_code *ec);
const char		*error_message(const t_error_code *ec);

#endif
