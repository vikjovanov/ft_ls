/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 08:42:38 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 14:43:44 by vjovanov         ###   ########.fr       */
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
static char	*fill_back_dir_path(char *path)
{
	char *new_path;

	if (ft_strequ(path, "."))
		new_path = ft_strdup("./");
	else if (ft_strequ(path, ".."))
		new_path = ft_strdup("../");
	else
		new_path = (ft_strchr(path, '/') == NULL) ? 
			ft_strjoin(path, "/") : ft_strdup(path);
	return (new_path);
}

t_dir		*insert_back_dir(t_dir *dir, char *path, char *parent)
{
	t_dir *new;
	t_dir *tmp;

	if (path == NULL || (new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (parent == NULL)
		new->parent = ft_strdup("");
	else if (parent != NULL && ft_strequ(parent, "."))
		new->parent = ft_strdup("./");
	else if (parent != NULL && ft_strequ(parent, ".."))
		new->parent = ft_strdup("../");
	else
		new->parent = (ft_strchr(parent, '/') == NULL) ?
			ft_strjoin(parent, "/") : ft_strdup(parent);
	new->pathname = fill_back_dir_path(path);
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