/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 10:01:28 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/18 10:01:30 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	regular_print(t_file *lst_file, int	print_mult_dir, t_field min_field)
{
	printf("%s\n", );
}

t_field	*find_min_field_width(t_file *file)
{
	t_field	*min_field_width;
	t_file *tmp;

	if ((min_field_width = malloc(sizeof(min_field_width*))) == NULL)
		exit(EXIT_FAILURE);
	tmp = file;
	while (tmp != NULL)
	{
		if ((int)ft_strlen(file->number_of_link) > min_field_width->n_link)
			min_field_width->n_link = (int)ft_strlen(file->number_of_link);
		if ((int)ft_strlen(file->owner_name) > min_field_width->user_name)
			min_field_width->user_name = (int)ft_strlen(file->owner_name);
		if ((int)ft_strlen(file->group_name) > min_field_width->group_name)
			min_field_width->group_name = (int)ft_strlen(file->group_name);
		if ((int)ft_strlen(file->size_byte) > ())
		tmp = tmp->next;
	}
	return (min_field_width);
}

void	dispatch_print(t_file *lst_file, int print_mult_dir)
{
	t_field *min_field_width;

	min_field_width = find_min_field_width(lst_file);
	while (lst_file != NULL)
	{
		if (ft_strchr("spdl", lst_file->file_type))
			regular_print(lst_file, print_mutiple_dir);
		else if (ft_strchr("bc", lst_file->file_type))
			special_print(lst_file, print_mutiple_dir);
		lst_file = lst_file->next;
	}
}
