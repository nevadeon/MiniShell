#include "test.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char ** argv, char **envp)
{
	test_memory();
	test_parsing(&envp);
	return (EXIT_SUCCESS);
}
