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
/*
t_dir	*insert_after_elem_dir(t_dir *dir, t_dir *ref_dir,
	char *path, char *parent)
{
	t_dir *new;

	new = malloc(sizeof(*new));
	new->parent = parent;
	new->pathname = path;
}

t_dir	*insert_before_elem_dir(t_dir *dir, t_dir *ref_dir,
	char *path, char *parent)
{
	t_dir *new;

	new = malloc(sizeof(*new));
	new->parent = parent;
	new->pathname = path;

}
*/

t_dir		*insert_back_dir(t_dir *dir, char *path, char *parent)
{
	t_dir *new;
	t_dir *tmp;

	if (path == NULL || (new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (parent == NULL)
	{
		new->parent = ft_strdup("");
		new->pathname = ft_strdup(path);
	}
	else
	{
		new->parent = ft_strdup(parent);
		new->pathname = ft_strjoin("/", path);
	}
	if (new->parent == NULL || new->pathname == NULL)
		return (NULL);
	new->next = NULL;
	if (is_empty_dir(dir))
		return (new);
	tmp = dir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (dir);
}


///////////////////////////////////////////////////////

void	display_lst_dir(t_dir *dir)
{
	t_dir *tmp;

	tmp = dir;
	if (is_empty_dir(dir))
	{
		ft_printf("--\n");
		ft_printf("(null)\n");
		ft_printf("--\n");
	}
	while (dir != NULL)
	{
		ft_printf("--\n");
		ft_printf("path: %s\n", dir->pathname);
		ft_printf("parent: %s\n", dir->parent);
		ft_printf("--\n");
		dir = dir->next;
	}
	dir = tmp;
}