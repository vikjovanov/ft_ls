/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_nav.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:14:23 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 22:27:48 by vjovanov         ###   ########.fr       */
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
		if (stat(pathname, &infos_element) == -1)
			generic_error(dir_element->d_name);
		if ((LST_FILE = insert_back_file(LST_FILE, &infos_element, dir_element->d_name)) == NULL)
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
	if (LST_DIR->parent == NULL)
		path = LST_DIR->pathname;
	else
		if ((path = ft_strjoin(LST_DIR->parent, LST_DIR->pathname)) == NULL)
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
		generic_error(LST_DIR->pathname);
	//display_lst_file(LST_FILE);
	//LST_FILE = order_file(LST_FILE);
	return (1);
}
