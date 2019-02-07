/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 08:42:38 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 19:54:54 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(void)
{
	return (NULL);
}

t_dir	*insert_child_dir(t_dir *lst_dir, t_dir *new_dirs)
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
	parent = NULL;
	while (tmp != NULL)
	{
		if ((parent = (LST_DIR->parent == NULL) ? ft_strdup(LST_DIR->pathname)
			: ft_strjoin(LST_DIR->parent, LST_DIR->pathname)) == NULL)
			return (NULL);
		if (tmp->file_type == 'd' && !(ft_strequ(tmp->pathname, ".")
			|| ft_strequ(tmp->pathname, "..")))
			new_dirs = insert_back_dir(new_dirs, tmp->pathname,
				parent);
		ft_memdel((void**)&(parent));
		tmp = tmp->next;
	}
	lst_dir = insert_child_dir(lst_dir, new_dirs);
	new_dirs = NULL;
	return (lst_dir);
}

t_dir	*insert_front_dir(t_dir *dir, char *path, char *parent)
{
	t_dir *new;

	if (path == NULL || (new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (parent == NULL)
	{
		new->parent = ft_strdup("");
		new->pathname = ft_strdup(path);
	}
	else
	{
		new->parent = ft_strdup(path);
		new->pathname = ft_strjoin("/", path);
	}
	if (new->parent == NULL || new->pathname == NULL)
		return (NULL);
	if (is_empty_dir(dir))
		new->next = NULL;
	else
		new->next = dir;
	return (new);
}

t_dir	*insert_back_dir(t_dir *dir, char *path, char *parent)
{
	t_dir *new;
	t_dir *tmp;

	if (path == NULL || (new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (parent == NULL)
		new->parent = ft_strdup("");
	if (parent == NULL)
		new->pathname = ft_strdup(path);
	if (parent != NULL)
		new->parent = ft_strdup(parent);
	if (parent != NULL)
		new->pathname = (ft_strequ(parent, "/"))
			? ft_strdup(path) : ft_strjoin("/", path);
	new->next = NULL;
	if (new->parent == NULL || new->pathname == NULL)
		return (del_front_dir(new));
	if (is_empty_dir(dir))
		return (new);
	tmp = dir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (dir);
}

/*
** void	display_lst_dir(t_dir *dir)
** {
**	t_dir *tmp;
**
**	tmp = dir;
**	if (is_empty_dir(dir))
**	{
**		ft_printf("--\n");
**		ft_printf("(null)\n");
**		ft_printf("--\n");
**	}
**	while (dir != NULL)
**	{
**		ft_printf("--\n");
**		ft_printf("path: %s\n", dir->pathname);
**		ft_printf("parent: %s\n", dir->parent);
**		ft_printf("--\n");
**		dir = dir->next;
**	}
**	dir = tmp;
** }
*/
