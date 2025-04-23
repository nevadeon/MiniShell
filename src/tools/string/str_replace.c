#include "str.h"
#include "mem.h"

void	str_replace(t_lifetime lft, t_replace data)
{
	char	*old_str;
	char	*new_word;
	size_t	str_l;
	size_t	rep_l;
	size_t	new_word_l;

	old_str = *data.str;
	rep_l = str_len(data.rep);
	str_l = str_len(old_str);
	new_word_l = str_l - (data.end - data.start) + rep_l;
	new_word = mem_alloc(lft, (new_word_l + 1) * sizeof(char));
	if (!new_word)
		return ;
	str_memcpy(new_word, old_str, data.start);
	str_memcpy(new_word + data.start, data.rep, rep_l);
	str_memcpy(new_word + data.start + rep_l, old_str + data.end, str_l - data.end);
	new_word[new_word_l] = '\0';
	*data.str = NULL;
	*data.str = new_word;
}
