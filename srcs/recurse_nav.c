/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_nav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:14:23 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 21:22:29 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_lst_file(DIR *current_dir, char *path)
{
	struct dirent *dir_element;
	struct stat	infos_element;
	char	*pathname;

	if ((dir_element = readdir(current_dir)) != NULL)
	{
		if (!(PARAMS & PARAM_A) && dir_element->d_name[0] == '.')
			return (1);
		if ((pathname = ft_strjoin(path, dir_element->d_name)) == NULL)
			return (0);
		if (lstat(pathname, &infos_element) == -1)
			generic_error(dir_element->d_name);
		if ((LST_FILE = insert_back_file(LST_FILE, &infos_element,
				dir_element->d_name, pathname)) == NULL)
		{
			ft_memdel((void**)&(pathname));
			return (0);
		}
		ft_memdel((void**)&(pathname));
	}
	else
		return (-1);
	return (1);
}

static int 	free_path(char *path)
{
	ft_memdel((void**)&(path));
	return (1);
}

int		recurse_nav(void)
{
	DIR 	*current_dir;
	char	*path;
	int		result;
	char	*tmp;

	result = 0;
	tmp = ft_strjoin(LST_DIR->parent, LST_DIR->pathname);
	path = ft_strjoin(tmp, "/");
	ft_memdel((void**)&(tmp));
	if (path == NULL)
		return (0);
	if ((current_dir = opendir(path)))
	{
		while (current_dir)
		{
			if ((result = fill_lst_file(current_dir, path)) == -1)
				break ;
			else if (result == 0)
				return (!free_path(path));
		}
		closedir(current_dir);
	}
	else
		generic_error(LST_DIR->pathname);
	return (!free_path(path));
}
