/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:44:18 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/14 14:44:19 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*new_file(void)
{
	t_file *new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->filemode = NULL;
	new->permission = 0;
	new->number_of_link = 0;
	new->owner_name = NULL;
	new->group_name = NULL;
	new->size_byte = 0;
	new->last_modif = 0;
	new->pathname = NULL;
	new->next = NULL;
	return (new);
}

t_file	*insert_front_file(t_file *dir, char *path, char *parent)
{
	t_dir *new;

	if (path == NULL)
		return (NULL);
	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->parent = parent;
	new->pathname = path;
	if (is_empty_dir(dir))
		new->next = NULL;
	else
		new->next = dir;
	return (new);

}
/*
t_dir	*insert_after_elem_file(t_dir *dir, t_dir *ref_dir,
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
t_dir	*insert_back_file(t_dir *dir, char *path, char *parent)
{
	t_dir *new;
	t_dir *tmp;

	if (path == NULL)
		return (NULL);
	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->parent = parent;
	new->pathname = path;
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

void	display_lst_file(t_dir *dir)
{
	t_dir *tmp;

	tmp = dir;
	if (is_empty_dir(dir))
	{
		printf("--\n");
		printf("(null)\n");
		printf("--\n");
	}
	while (dir != NULL)
	{
		printf("--\n");
		printf("path: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("--\n");
		dir = dir->next;
	}
	dir = tmp;
}