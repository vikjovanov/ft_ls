/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 10:01:28 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 21:28:56 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	regular_print(t_file *lst_file, t_field *min_field)
{
	if ((g_global.params & PARAM_L))
	{
		ft_printf("%*d ", min_field->n_link, lst_file->number_of_link);
		ft_printf("%-*s  ", min_field->user_name, lst_file->owner_name);
		if (!(g_global.params & PARAM_O))
			ft_printf("%-*s  ", min_field->group_name, lst_file->group_name);
		if (ft_strchr("bc", lst_file->file_type))
			ft_printf("%*u, ", min_field->major, lst_file->major);
		else
			ft_printf("%*s", min_field->major + 2, "");
		if (ft_strchr("bc", lst_file->file_type))
			ft_printf("%*u ", min_field->size_byte, lst_file->minor);
		else
			ft_printf("%*ld ", min_field->size_byte, lst_file->size_byte);
		ft_printf("%s ", lst_file->modif_month);
		ft_printf("%s ", lst_file->modif_day);
		ft_printf("%*s ", min_field->modif_hy, (lst_file->modif_hours
			!= NULL) ? lst_file->modif_hours : lst_file->modif_years);
	}
	if (lst_file->file_type == 'l' && (PARAMS & PARAM_L))
		ft_printf("%s -> %s\n", lst_file->pathname, lst_file->symlink);
	else
		ft_printf("%s%s\n", lst_file->pathname, ((g_global.params & PARAM_P) &&
			lst_file->file_type == 'd') ? "/" : "");
}

void	permission_print(t_file *lst_file)
{
	ft_printf("%c", lst_file->file_type);
	ft_printf("%c", (lst_file->permission & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (lst_file->permission & S_IWUSR) ? 'w' : '-');
	if ((S_ISUID & lst_file->permission) != 0)
		ft_printf("%c", (lst_file->permission & S_IXUSR) ? 's' : 'S');
	else
		ft_printf("%c", (lst_file->permission & S_IXUSR) ? 'x' : '-');
	ft_printf("%c", (lst_file->permission & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (lst_file->permission & S_IWGRP) ? 'w' : '-');
	if ((S_ISGID & lst_file->permission) != 0)
		ft_printf("%c", (lst_file->permission & S_IXGRP) ? 's' : 'S');
	else
		ft_printf("%c", (lst_file->permission & S_IXGRP) ? 'x' : '-');
	ft_printf("%c", (lst_file->permission & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (lst_file->permission & S_IWOTH) ? 'w' : '-');
	if ((S_ISVTX & lst_file->permission) != 0)
		ft_printf("%c", (lst_file->permission & S_IXOTH) ? 't' : 'T');
	else
		ft_printf("%c", (lst_file->permission & S_IXOTH) ? 'x' : '-');
	if (lst_file->has_xattr == 1)
		ft_printf("%-2s", "@");
	else
		ft_printf("%-2s", (lst_file->has_xattr) == 2 ? "+" : "");
}

t_file	*dispatch_print(t_file *lst_file, int print_mult_dir, int print_newline)
{
	t_field *min_field_width;

	min_field_width = find_min_field_width(lst_file);
	if (print_mult_dir == 1)
		ft_printf("%s%s:\n", (LST_DIR->parent == NULL
			|| LST_DIR->parent == "/") ? "" : LST_DIR->parent,
			LST_DIR->pathname);
	if (length_file(lst_file) > 0)
	{
		if ((PARAMS & PARAM_L) && print_mult_dir != 2)
			ft_printf("total %lld\n", total_block(lst_file));
		while (lst_file != NULL)
		{
			if (PARAMS & PARAM_L)
				permission_print(lst_file);
			regular_print(lst_file, min_field_width);
			lst_file = del_front_file(lst_file);
		}
	}
	if (print_newline)
		if (print_mult_dir == 2 || length_dir(LST_DIR) > 1)
			ft_printf("\n");
	ft_memdel((void**)&(min_field_width));
	return (lst_file);
}
