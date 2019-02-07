/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 11:35:46 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 19:58:45 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_empty_dir(t_dir *dir)
{
	if (dir == NULL)
		return (1);
	return (0);
}

t_dir	*del_back_dir(t_dir *dir)
{
	t_dir *tmp;
	t_dir *tmp2;

	tmp = dir;
	tmp2 = NULL;
	if (is_empty_dir(dir))
		return (NULL);
	while (dir->next != NULL)
	{
		tmp2 = dir;
		dir = dir->next;
	}
	ft_memdel((void**)&dir->parent);
	ft_memdel((void**)&dir->pathname);
	dir->next = NULL;
	ft_memdel((void**)&dir);
	tmp2->next = NULL;
	return (tmp);
}

t_dir	*del_front_dir(t_dir *dir)
{
	t_dir *tmp;

	if (is_empty_dir(dir))
		return (NULL);
	tmp = dir->next;
	ft_memdel((void**)&(dir->parent));
	ft_memdel((void**)&(dir->pathname));
	dir->next = NULL;
	ft_memdel((void**)&dir);
	return (tmp);
}

t_dir	*clear_dir(t_dir *dir)
{
	if (dir->next != NULL)
		return (clear_dir(dir->next));
	free(dir);
	dir = NULL;
	return (dir);
}

size_t	length_dir(t_dir *dir)
{
	size_t	size;
	t_dir	*tmp;

	size = 0;
	tmp = dir;
	while (dir != NULL)
	{
		size++;
		dir = dir->next;
	}
	dir = tmp;
	return (size);
}
