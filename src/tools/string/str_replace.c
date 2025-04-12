#include "str.h"
#include "mem.h"

void	str_replace(char **str, char *rep, int start, int end)
{
	char	*old_str;
	char	*new_word;
	size_t  str_l;
	size_t  rep_l;
	size_t  new_word_l;

	old_str = *str;
	rep_l = str_len(rep);
	str_l = str_len(old_str);
	new_word_l = str_l - (end - start) + rep_l;
	new_word =	mem_alloc(E_LFT_TASK, (new_word_l + 1) * sizeof(char));
	if (!new_word)
		return;
	str_memcpy(new_word, old_str, start);
	str_memcpy(new_word + start, rep, rep_l);
	str_memcpy(new_word + start + rep_l, old_str + end, str_l - end);
	new_word[new_word_l] = '\0';
	*str = NULL;
	*str = new_word;
}
