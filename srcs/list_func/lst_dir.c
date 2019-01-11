/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 08:42:38 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/11 08:42:39 by vjovanov         ###   ########.fr       */
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

	new = malloc(sizeof(*new));
	new->parent = parent;
	new->pathname = path;
	if (is_empty_dir(dir))
		new->next = NULL;
	else
		new->next = dir;
	return (new);

}

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

t_dir	*insert_back_dir(t_dir *dir, char *path, char *parent)
{
	t_dir *new;
	t_dir *tmp;

	new = malloc(sizeof(*new));
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
