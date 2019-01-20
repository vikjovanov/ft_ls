/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_nav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:14:23 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 17:58:09 by vjovanov         ###   ########.fr       */
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
		//if (!(PARAMS & PARAM_A) && dir_element->d_name[0] == '.')
		//	return (1);
		if ((pathname = ft_strjoin(path, dir_element->d_name)) == NULL)
			return (0);
		if (stat(pathname, &infos_element) == -1)
			if (lstat(pathname, &infos_element) == -1)
				generic_error(dir_element->d_name);
		if ((LST_FILE = insert_back_file(LST_FILE, &infos_element,
				dir_element->d_name, pathname)) == NULL)
			return (0);
	}
	else
		return (-1);
	return (1);
}

int		recurse_nav(void)
{
	DIR *current_dir;
	char	*path;
	int		result;

	result = 0;
	if (ft_strequ(LST_DIR->parent, "") && ft_strequ(LST_DIR->pathname, "."))
		path = "./";
	else if (ft_strequ(LST_DIR->parent, "") && ft_strequ(LST_DIR->pathname, ".."))
		path = "../";
	else if (LST_DIR->parent == NULL)
		path = ft_strdup(LST_DIR->pathname);
	else
		path = ft_strjoin(LST_DIR->parent, LST_DIR->pathname);
	if (path == NULL)
		return (0);
	if ((current_dir = opendir(path)))
		while (current_dir)
		{
			if ((result = fill_lst_file(current_dir, path)) == -1)
				break ;
			else if (result == 0)
				return (0);
		}
	else
	{
		printf("cette erreur\n");
		generic_error(LST_DIR->pathname);
	}
	return (1);
}
