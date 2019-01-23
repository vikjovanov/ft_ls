/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 09:23:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 21:25:11 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Definition of "extern t_global g_global" in header file
*/

t_global	g_global = {0, NULL, NULL};

t_dir	*insert_child_dir(t_dir *lst_dir, t_dir	*new_dirs)
{
	t_dir	*tmp;

	if (new_dirs == NULL)
		return (lst_dir);
	tmp = new_dirs;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = lst_dir->next;
	lst_dir->next = new_dirs;
	return (lst_dir);
}

t_dir	*fill_lst_dir(t_file *lst_file, t_dir *lst_dir)
{
	t_file	*tmp;
	t_dir	*new_dirs;
	char	*parent;

	tmp = lst_file;
	new_dirs = new_dir();
	while (tmp != NULL)
	{
		if ((parent = (LST_DIR->parent == NULL) ? ft_strdup(LST_DIR->pathname)
			: ft_strjoin(LST_DIR->parent, LST_DIR->pathname)) == NULL)
			return (NULL);
		if (tmp->file_type == 'd' && !(ft_strequ(tmp->pathname, ".")
			|| ft_strequ(tmp->pathname, "..")))
			new_dirs = insert_back_dir(new_dirs, tmp->pathname,
				parent);
		tmp = tmp->next;
	}
	lst_dir = insert_child_dir(lst_dir, new_dirs);
	new_dirs = NULL;
	return (lst_dir);
}

int		main(int argc, char **argv)
{
	int		multi_dir;

	LST_DIR = new_dir();
	LST_FILE = new_file();
	if (!(arg_checker(argc, argv)))
		exit(EXIT_FAILURE);
	//display_lst_file(LST_FILE);
	//if (is_empty_dir(LST_DIR) && is_empty_file(LST_FILE))
	//	if ((LST_DIR = insert_front_dir(LST_DIR, ".", NULL)) == NULL)
	//		return (0);
	multi_dir = ((PARAMS & PARAM_RR) || length_dir(LST_DIR) >= 2 ||
		(!is_empty_file(LST_FILE))) ? 1 : 0;
	if (!(is_empty_file(LST_FILE)))
		dispatch_print(LST_FILE, 2);
	//display_lst_dir(LST_DIR);
	while (!is_empty_dir(LST_DIR))
	{
		LST_FILE = new_file();
		if (!(recurse_nav()))
			exit(EXIT_FAILURE);
		//display_lst_file(LST_FILE);
		//display_lst_dir(LST_DIR);
		LST_FILE = lst_order_file(LST_FILE);
		if (PARAMS & PARAM_RR)
			LST_DIR = fill_lst_dir(LST_FILE, LST_DIR);		
		LST_FILE = dispatch_print(LST_FILE, multi_dir);
		LST_DIR = del_front_dir(LST_DIR);
		ft_memdel((void**)&(LST_FILE));
	}
	return (0);
}