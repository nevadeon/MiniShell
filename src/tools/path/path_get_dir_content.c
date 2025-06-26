/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_get_dir_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:49 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/path.h"
#include "tools/sort.h"

t_list	*path_get_dir_content(t_alloc *alloc, char *path)
{
	t_list			*list;
	struct dirent	*ent;
	struct stat		st;
	DIR				*rep;
	char			*file_path;

	rep = opendir(path);
	list = NULL;
	if (rep == NULL)
		return (perror("Error while opening repository"), NULL);
	if (str_equals(path, "."))
		path = "";
	while (1)
	{
		ent = readdir(rep);
		if (!ent)
			break ;
		file_path = str_vjoin(alloc, 2, path, ent->d_name);
		if (str_equals(ent->d_name, ".") || str_equals(ent->d_name, ".."))
			continue ;
		if (stat(file_path, &st) == 0)
			lst_add_back(&list, lst_new(alloc, (void *)file_path));
	}
	closedir(rep);
	return (ft_qsort(list, ascii_sort));
}
