/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:45:05 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/22 18:45:06 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// MAJOR A GAUCHE ET MINOR A DROITE A LA PLACE DE SIZE_BYTE

static void	min_field_width_special(t_field *mfw, t_file *tmp)
{
	mfw->major = 0;
	if ((int)ft_nblen(tmp->major) > mfw->major)
		mfw->major = (int)ft_nblen(tmp->major);
	if ((int)ft_nblen(tmp->minor) > mfw->size_byte)
		mfw->size_byte = (int)ft_nblen(tmp->minor);
}

t_field		*find_min_field_width(t_file *file)
{
	t_field	*min_field_width;
	t_file *tmp;

	if ((min_field_width = malloc(sizeof(t_field))) == NULL)
		exit(EXIT_FAILURE);
	min_field_width->n_link = 1;
	min_field_width->user_name = 0;
	min_field_width->group_name = 0;
	min_field_width->size_byte = 1;
	tmp = file;
	while (tmp != NULL)
	{
		if ((int)ft_nblen(tmp->number_of_link) > min_field_width->n_link)
			min_field_width->n_link = (int)ft_nblen(tmp->number_of_link);
		if ((int)ft_strlen(tmp->owner_name) > min_field_width->user_name)
			min_field_width->user_name = (int)ft_strlen(tmp->owner_name);
		if ((int)ft_strlen(tmp->group_name) > min_field_width->group_name)
			min_field_width->group_name = (int)ft_strlen(tmp->group_name);
		if (((int)ft_nblen(tmp->size_byte) > min_field_width->size_byte))
			min_field_width->size_byte = (int)ft_nblen(tmp->size_byte);
		if (file->file_type == 'c' || file->file_type == 'b')
			min_field_width_special(min_field_width, tmp);
		tmp = tmp->next;
	}
	return (min_field_width);
}

long long	total_block(t_file *lst_file)
{
	long long total;
	t_file *tmp;

	tmp = lst_file;
	total = 0;
	while (tmp != NULL)
	{
		total += tmp->block_512kb;
		tmp = tmp->next;
	}
	return (total);
}
