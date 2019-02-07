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

static int			free_path(char *path)
{
	ft_memdel((void**)&(path));
	return (1);
}

int					fill_lst_file(DIR *current_dir, char *path)
{
	struct dirent	*dir_element;
	struct stat		infos_element;
	char			*pathname;

	if ((dir_element = readdir(current_dir)) != NULL)
	{
		if (!(PARAMS & PARAM_A) && dir_element->d_name[0] == '.')
			return (1);
		if ((pathname = ft_strjoin(path, dir_element->d_name)) == NULL)
			return (0);
		if (lstat(pathname, &infos_element) == -1)
			return (free_path(pathname));
		if ((LST_FILE = insert_back_file(LST_FILE, &infos_element,
				dir_element->d_name, pathname)) == NULL)
			return (free_path(pathname));
		ft_memdel((void**)&(pathname));
	}
	else
		return (-1);
	return (1);
}

static int			error_dir(char *path, int multi_dir)
{
	char *element;

	element = (LST_DIR->pathname[0] == '/') ?
		ft_strdup(&(LST_DIR->pathname[1])) : ft_strdup(LST_DIR->pathname);
	LST_FILE = dispatch_print(LST_FILE, multi_dir, 0);
	generic_error(element);
	if (length_dir(LST_DIR) > 1)
		ft_printf("\n");
	ft_memdel((void**)&(element));
	return (free_path(path));
}

int					recurse_nav(int multi_dir)
{
	DIR		*current_dir;
	char	*path;
	int		result;
	char	*tmp;

	result = 0;
	tmp = ft_strjoin(LST_DIR->parent, LST_DIR->pathname);
	path = (ft_strequ(tmp, "/")) ? ft_strdup(tmp) : ft_strjoin(tmp, "/");
	if (path == NULL)
		return (!free_path(tmp));
	ft_memdel((void**)&(tmp));
	if ((current_dir = opendir(path)))
	{
		while (current_dir)
			if ((result = fill_lst_file(current_dir, path)) == -1)
				break ;
			else if (result == 0 && free_path(path))
				exit_failure();
		closedir(current_dir);
	}
	else
		return (!error_dir(path, multi_dir));
	return (free_path(path));
}
