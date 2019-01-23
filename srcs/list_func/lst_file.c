/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:44:18 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 21:25:05 by vjovanov         ###   ########.fr       */
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

static void	set_major_minor(t_file *new, struct stat *file)
{
	if (new->file_type != 'c' && new->file_type != 'b')
	{
		new->major = 0;
		new->minor = 0;
		return ;
	}
	new->major = ((file->st_rdev) >> MINORBITS);
	new->minor = ((file->st_rdev) & MINORMASK);
}

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
	new->modif_timestamps = file->st_mtime;
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
	mode = ((file->st_mode & S_IFMT) == S_IFDIR ? 'd' : mode);
	return (mode);
}

char	*set_symlink(char *path, char *name_file)
{
	char	*symlink;
	ssize_t	size_sym;

	symlink = ft_strnew(MAX_LENGTH_FILENAME);
	if ((size_sym = readlink(path, symlink, sizeof(symlink))) < 0)
		generic_error(name_file);
	return (symlink);
}

int		fill_xattr(char *path)
{
	int 	size;

	size = 0;
	size = (int)listxattr(path, NULL, size, 0);
	if (size < 0)
		return (-1);
	else if (size == 0)
		return (0);
	else
		return (1);
}

t_file	*fill_link(t_file *new, struct stat *file, char *file_name, char *path)
{
	struct passwd *usr_info;
	struct group *grp_info;

	usr_info = getpwuid(file->st_uid);	
	grp_info = getgrgid(file->st_gid);
	new->file_type = set_file_type(file);	
	new->permission = file->st_mode;
	new->has_xattr = fill_xattr(path);
	new->number_of_link = file->st_nlink;
	new->owner_name = (usr_info != NULL) ? ft_strdup(usr_info->pw_name)
		: ft_itoa((int)(file->st_uid));
	new->group_name = (grp_info != NULL) ? ft_strdup(grp_info->gr_name)
		: ft_itoa((int)(file->st_gid));
	new->size_byte = file->st_size;
	set_major_minor(new, file);
	new->block_512kb = file->st_blocks;
	if (!(fill_last_modif(new, file)))
		return (NULL);	
	new->symlink = (new->file_type == 'l') ?
		set_symlink(path, file_name) : NULL;		
	new->pathname = ft_strdup(file_name);	
	if (!(new->owner_name) || !(new->group_name) || !(new->pathname))
		return (NULL);	
	new->next = NULL;
	return (new);
}

t_file	*insert_back_file(t_file *lst_file, struct stat *file,
	char *file_name, char *path)
{
	t_file *new;
	t_file *tmp;

	if ((new = malloc(sizeof(t_file))) == NULL)
		return (NULL);
	if ((new = fill_link(new, file, file_name, path)) == NULL)
		return (NULL);
	if (is_empty_file(lst_file))
		return (new);	
	tmp = lst_file;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp = NULL;
	return (lst_file);
}

t_file	*move_front_file(t_file *lst_file, t_file *element)
{
	t_file	*tmp;
	t_file	*previous;

	tmp = lst_file;
	if (lst_file == element)
		return (lst_file);
	while (tmp != element)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	previous->next = element->next;
	element->next = lst_file;
	return (element);
}


///////////////////////////////////////////////////////

void	display_lst_file(t_file *file)
{
	t_file *tmp;

	tmp = file;
	while (file != NULL)
	{
		ft_printf("\n-- file --\n");
		ft_printf("name: %s\n", file->pathname);
		ft_printf("type: %c\n", file->file_type);
		ft_printf("permission: %d\n", file->permission);
		ft_printf("number link: %d\n", file->number_of_link);
		ft_printf("owner: %s\n", file->owner_name);
		ft_printf("group: %s\n", file->group_name);
		ft_printf("size_byte: %ld\n", file->size_byte);
		ft_printf("modif_timestamps: %ld\n", file->modif_timestamps);
		ft_printf("modif_ctime: %s\n", ctime(&(file->modif_timestamps)));
		ft_printf("block 512 : %lld\n", file->block_512kb);
		if (file->file_type == 'b' || file->file_type == 'c')
		{
			ft_printf("major : %u\n", file->major);
			ft_printf("minor : %u\n", file->minor);
		}
		ft_printf("my_adress: %p\n", file);
		ft_printf("adress next: %p\n", file->next);

		//ft_printf("last_modif: %s", ctime(&(file->last_modif)));
		ft_printf("----------\n");
		file = file->next;
	}
	file = tmp;
}
