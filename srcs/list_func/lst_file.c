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

int 	fill_link_ext(t_file *new, struct stat *file, char *file_name)
{
	struct passwd *usr_info;
	struct group *grp_info;

	usr_info = getpwuid(file->st_uid);	
	grp_info = getgrgid(file->st_gid);
	new->owner_name = (usr_info != NULL) ? ft_strdup(usr_info->pw_name)
		: ft_itoa((int)(file->st_uid));
	new->group_name = (grp_info != NULL) ? ft_strdup(grp_info->gr_name)
		: ft_itoa((int)(file->st_gid));
	new->pathname = ft_strdup(file_name);
	if (!(new->owner_name) || !(new->group_name) || !(new->pathname))
		return (0);
	return (1);

}

t_file	*fill_link(t_file *new, struct stat *file, char *file_name, char *path)
{
	int res;
	int res2;

	new->file_type = set_file_type(file);	
	new->permission = file->st_mode;
	new->has_xattr = fill_xattr(path);
	new->number_of_link = file->st_nlink;
	new->size_byte = file->st_size;
	set_major_minor(new, file);
	res = fill_link_ext(new, file, file_name);
	new->block_512kb = file->st_blocks;
	res2 = fill_last_modif(new, file);
	new->symlink = (new->file_type == 'l') ?
		set_symlink(path, file_name) : NULL;
	new->next = NULL;
	if (!res || !res2 || (new->file_type == 'l' && new->symlink == NULL))
	{
		del_front_file(new);
		return (NULL);
	}
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
