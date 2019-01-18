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
	return (NULL);
}
/*
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
*/
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

/*
** (((3600*24)*30)*6)=6mois=15552000
*/

static int	fill_last_modif(t_file *new, struct stat *file)
{
	time_t timer;
	time_t diff;

	timer = time(&timer);
	new->modif_hours = NULL;
	new->modif_years = NULL;
	if ((diff = timer - file->st_mtime) < 0)
		diff *= -1;
	if ((timer - file->st_mtime) < 15552000)
		new->modif_hours = ft_strsub(ctime(&(file->st_mtime)), 11, 5);
	else
		new->modif_years = ft_strsub(ctime(&(file->st_mtime)), 20, 4);
	new->modif_day = ft_strsub(ctime(&(file->st_mtime)), 8, 2);
	new->modif_month = ft_strsub(ctime(&(file->st_mtime)), 4, 3);
	if (new->modif_day == NULL || new->modif_month == NULL ||
		(new->modif_hours == NULL && new->modif_years == NULL))
		return (0);
	return (1);
}

static char	set_file_type(struct stat *file)
{
	char	mode;

	mode = 0;
	mode = ((file->st_mode & S_IFMT) == S_IFREG ? '-' : mode);
	mode = ((file->st_mode & S_IFMT) == S_IFCHR ? 'c' : mode);
	mode = ((file->st_mode & S_IFMT) == S_IFBLK ? 'b' : mode);
	mode = ((file->st_mode & S_IFMT) == S_IFIFO ? 'p' : mode);
	mode = ((file->st_mode & S_IFMT) == S_IFSOCK ? 's' : mode);
	mode = ((file->st_mode & S_IFMT) == S_IFLNK ? 'l' : mode);
	return (mode);
}

t_file *fill_link(t_file *new, struct stat *file, char *file_name)
{
	struct passwd *usr_info;
	struct group *grp_info;

	usr_info = getpwuid(file->st_uid);
	grp_info = getgrgid(file->st_gid);
	new->file_type = set_file_type(file);
	new->permission = file->st_mode;
	new->number_of_link = file->st_nlink;
	new->owner_name = usr_info->pw_name;
	new->group_name = grp_info->gr_name;
	new->size_byte = file->st_size;
	if (!(fill_last_modif(new, file)))
		return (NULL);
	new->pathname = file_name;
	new->next = NULL;
	return (new);
}

t_file	*insert_back_file(t_file *lst_file, struct stat *file, char *file_name)
{
	t_file *new;
	t_file *tmp;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new = fill_link(new, file, file_name);
	if (is_empty_file(lst_file))
		return (new);
	tmp = lst_file;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (lst_file);
}


///////////////////////////////////////////////////////

void	display_lst_file(t_file *file)
{
	t_file *tmp;

	tmp = file;
	while (file != NULL)
	{
		printf("\n-- file --\n");
		printf("name: %s\n", file->pathname);
		printf("type: %c\n", file->file_type);
		printf("permission: %ld\n", file->permission);
		printf("number link: %d\n", file->number_of_link);
		printf("owner: %s\n", file->owner_name);
		printf("group: %s\n", file->group_name);
		printf("size_byte: %ld\n", file->size_byte);
		//printf("last_modif: %s", ctime(&(file->last_modif)));
		printf("----------\n");
		file = file->next;
	}
	file = tmp;
}
