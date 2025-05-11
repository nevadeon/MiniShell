#include "error.h"
#include <stdio.h>

const char	*error_name(const t_error_code *ec)
{
	return (ec->error_category->name());
}

const char	*error_message(const t_error_code *ec)
{
	return (ec->error_category->message(ec->value));
}

t_error_code	make_error(int val, const t_error_category *cat)
{
	t_error_code	ec;

	ec.value = val;
	ec.error_category = cat;
	return (ec);
}

