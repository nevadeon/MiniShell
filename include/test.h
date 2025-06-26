/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:51 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 16:02:07 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "forward.h"
# include <assert.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include "tools/str.h"
# include "minishell.h"
# include "allocators/allocator.h"

bool	test_memory(void);
void	test_parsing(char ***envp);

#endif
