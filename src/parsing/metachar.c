/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:13 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_blank_meta(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
 * see : https://www.gnu.org/software///bash/manual/bash.html#Shell-Syntax
 *
*/
bool	is_meta(char c)
{
	return (is_blank_meta(c) || (c == '|' || c == '<' || c == '>'));
}

// bool	is_meta(char c)
// {
// 	return (is_blank_meta(c) || (c == '|'
// 		|| c == '&' || c == ';' || c == '(' || c == ')' || c == '<'
// 		|| c == ')' || c == '>'));
// }
