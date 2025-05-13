#include "path.h"
#include "sort.h"

t_list	*path_get_dir_content(char *path)
{
	t_list			*list;
	struct dirent	*ent;
	struct stat		st;
	DIR				*rep;
	char			*file_path;

	rep = opendir(path);
	list = NULL;
	if (rep == NULL)
		return (perror("Erreur lors de l'ouverture du répertoire"), NULL);
	if (str_equals(path, "."))
		path = "";
	while (1)
	{
		ent = readdir(rep);
		if (!ent)
			break ;
		file_path = str_vjoin(E_LFT_TASK, 2, path, ent->d_name);
		if (str_equals(ent->d_name, ".") || str_equals(ent->d_name, ".."))
			continue ;
		if (stat(file_path, &st) == 0)
			lst_add_back(&list, lst_new(E_LFT_TASK, (void *)file_path));
	}
	closedir(rep);
	return (ft_qsort(list, ascii_sort));
}
