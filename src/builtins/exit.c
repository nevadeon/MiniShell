#include "cbuiltins.h"
#include <stdio.h>
#include <limits.h>

static int	_parse_digits(const char *s, t_parser *parser, long long *res)
{
	int	digit;

	while (*s)
	{
		if (!char_isnum(*s))
			return (0);
		digit = *s - '0';
		if (parser->acc > (parser->limit - digit) / 10)
			return (-1);
		parser->acc = parser->acc * 10 + digit;
		s++;
	}
	*res = (long long)parser->acc * parser->sign;
	return (1);
}

static int	_parse_number(const char *s, long long *res)
{
	t_parser	parser;

	parser.sign = 1;
	parser.acc = 0;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			parser.sign = -1;
		s++;
	}
	if (!*s)
		return (0);
	if (parser.sign > 0)
		parser.limit = (unsigned long long)LLONG_MAX;
	else
		parser.limit = (unsigned long long)LLONG_MAX + 1ULL;
	return (_parse_digits(s, &parser, res));
}

static void	cleanup(t_ctx *ctx)
{
	free_allocator(ctx->cmd);
	free_allocator(ctx->prog);
}

static void	cleanup_and_exit(t_ctx *ctx, unsigned char code)
{
	cleanup(ctx);
	exit(code);
}

int	builtin_exit(t_ctx *ctx, char **args)
{
	long long	status;
	int			parsed;

	printf("exit\n");
	if (!args[1])
		cleanup_and_exit(ctx, (unsigned char)ctx->last_exit_code);
	parsed = _parse_number(args[1], &status);
	if (parsed != 1)
	{
		io_dprintf(\
			STDERR, "bash: exit: %s: numeric argument required\n", args[1]);
		free_allocator(ctx->cmd);
		free_allocator(ctx->prog);
		exit(2);
	}
	if (args[2])
	{
		io_dprintf(STDERR, "bash: exit: too many arguments\n");
		ctx->last_exit_code = 1;
		return (1);
	}
	cleanup_and_exit(ctx, (unsigned char)status);
	return (1);
}
