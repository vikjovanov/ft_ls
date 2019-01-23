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

static void	min_field_width_supp(t_field *mfw, t_file *tmp)
{
	int min_field_minor = 3;
	int	min_field_major = 3;

	if (tmp->modif_hours != NULL
		&& (int)ft_strlen(tmp->modif_hours) > mfw->modif_hy)
			mfw->modif_hy = (int)ft_strlen(tmp->modif_hours);
	if (tmp->modif_years != NULL
		&& (int)ft_strlen(tmp->modif_years) > mfw->modif_hy)
			mfw->modif_hy = (int)ft_strlen(tmp->modif_years);
	if (tmp->file_type == 'c' || tmp->file_type == 'b')
	{
		if (min_field_major > mfw->major)
			mfw->major = min_field_major;
		if ((int)ft_nblen(tmp->major) > mfw->major)
			mfw->major = (int)ft_nblen(tmp->major);
		if (min_field_minor > mfw->size_byte)
			mfw->size_byte = min_field_minor;
		if ((int)ft_nblen(tmp->minor) > mfw->size_byte)
			mfw->size_byte = (int)ft_nblen(tmp->minor);
	}
}

static t_field	*set_min_field(void)
{
	t_field *min_field_width;

	if ((min_field_width = malloc(sizeof(t_field))) == NULL)
		return (NULL);
	min_field_width->n_link = 1;
	min_field_width->user_name = 0;
	min_field_width->group_name = 0;
	min_field_width->major = -2 ;
	min_field_width->size_byte = 1;
	min_field_width->modif_hy = 0;
	return (min_field_width);
}

t_field		*find_min_field_width(t_file *file)
{
	t_field	*min_field_width;
	t_file *tmp;

	if (((min_field_width = set_min_field())) == NULL)
		return (NULL);
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
		min_field_width_supp(min_field_width, tmp);
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
