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
