/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 10:01:28 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 18:09:27 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	regular_print(t_file *lst_file, t_field *min_field)
{
	if (g_global.params & PARAM_L)
	{
	printf("%*d ", min_field->n_link, lst_file->number_of_link);
	printf("%*s  ", min_field->user_name, lst_file->owner_name);
	printf("%*s  ", min_field->group_name, lst_file->group_name);
	printf("%*ld ", min_field->size_byte, lst_file->size_byte);
	printf("%s ", lst_file->modif_month);
	printf("%s ", lst_file->modif_day);
	if (lst_file->modif_hours != NULL)
		printf("%s ", lst_file->modif_hours);
	else
		printf("%s ", lst_file->modif_years);
	}
	if (lst_file->file_type != 'l')
		printf("%s\n", lst_file->pathname);
	else
		printf("%s -> %s\n", lst_file->pathname, lst_file->symlink);

}

t_field	*find_min_field_width(t_file *file)
{
	t_field	*min_field_width;
	t_file *tmp;

	if ((min_field_width = malloc(sizeof(t_field))) == NULL)
		exit(EXIT_FAILURE);
	min_field_width->n_link = 2;
	min_field_width->user_name = 0;
	min_field_width->group_name = 0;
	min_field_width->size_byte = 2;
	tmp = file;
	while (tmp != NULL)
	{
		if ((int)ft_nblen(tmp->number_of_link) > min_field_width->n_link)
			min_field_width->n_link = (int)ft_nblen(tmp->number_of_link);
		if ((int)ft_strlen(tmp->owner_name) > min_field_width->user_name)
			min_field_width->user_name = (int)ft_strlen(tmp->owner_name);
		if ((int)ft_strlen(tmp->group_name) > min_field_width->group_name)
			min_field_width->group_name = (int)ft_strlen(tmp->group_name);
		if ((int)ft_nblen(tmp->size_byte) > min_field_width->size_byte)
			min_field_width->size_byte = (int)ft_nblen(tmp->size_byte);
		tmp = tmp->next;
	}
	return (min_field_width);
}

t_file	*dispatch_print(t_file *lst_file, int print_mult_dir)
{
	t_field *min_field_width;

	min_field_width = find_min_field_width(lst_file);
	if (print_mult_dir == 1 && !(ft_strequ(LST_DIR->pathname, "./") ||
		ft_strequ(LST_DIR->pathname, ".")))
		printf("%s%s:\n", (LST_DIR->parent == NULL) ? "" : LST_DIR->parent,
			LST_DIR->pathname);
	while (lst_file != NULL)
	{
		if (!(PARAMS & PARAM_A) && lst_file->pathname[0] == '.');
		else if (ft_strchr("spdl-", lst_file->file_type))
			regular_print(lst_file, min_field_width);
		//else if (ft_strchr("bc", lst_file->file_type))
			//special_print(lst_file, print_mult_dir, min_field_width);
		lst_file = del_front_file(lst_file);
	}
	if (length_dir(LST_DIR) > 1 && print_mult_dir == 1)
		printf("\n");
	return (lst_file);
}
