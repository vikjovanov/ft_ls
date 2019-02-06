/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fill_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:17:12 by vjovanov          #+#    #+#             */
/*   Updated: 2019/02/04 16:17:13 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_major_minor(t_file *new, struct stat *file)
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
** (((3600*24)*30)*6)=6mois=1.577e+7
*/

int		fill_last_modif(t_file *new, struct stat *file)
{
	time_t timer;
	time_t diff;

	timer = time(&timer);
	new->modif_hours = NULL;
	new->modif_years = NULL;
	new->modif_timestamps = file->st_mtime;
	if ((diff = timer - file->st_mtime) < 0)
		diff *= -1;
	if ((timer - file->st_mtime) < 1.577e+7)
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

char	set_file_type(struct stat *file)
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

	if ((symlink = ft_strnew(MAX_LENGTH_FILENAME)) == NULL)
		return (NULL);
	if ((size_sym = readlink(path, symlink, MAX_LENGTH_FILENAME)) < 0)
		generic_error(name_file);
	return (symlink);
}

int		fill_xattr(char *path)
{
	int 		size;
	//acl_t		acl;
	//acl_type_t  entry;
	//
	//struct stat *test = file;
	//test= NULL;
	//
	size = 0;
	size = (int)listxattr(path, NULL, size, 0);
	/*acl = acl_get_file(path, ACL_TYPE_ACCESS);
	if (acl == NULL)
	{
		printf("path : %s\n", path);
	}
	else
	{
		printf("youpii\n");
	}*/

	if (size < 0)
		return (-1);
	else if (size == 0)
		return (0);
	else
		return (1);
}
