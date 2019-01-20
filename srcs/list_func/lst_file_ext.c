/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:44:24 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 11:12:11 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_empty_file(t_file *file)
{
	if (file == NULL)
		return (1);
	return (0);
}

t_file	*del_back_file(t_file *file)
{
	t_file *tmp;
	t_file *tmp2;

	tmp = file;
	tmp2 = NULL;
	if (is_empty_file(file))
		return (NULL);
	while (file->next != NULL)
	{
		tmp2 = file;
		file = file->next;
	}
	free(file);
	file = NULL;
	tmp2->next = NULL;
	return (tmp);
}

t_file	*del_front_file(t_file *file)
{
	t_file *tmp;

	if (is_empty_file(file))
		return (NULL);
	tmp = file->next;
	free(file);
	file = NULL;
	return (tmp);
}

t_file	*clear_file(t_file *file)
{
	if (file->next != NULL)
		return (clear_file(file->next));
	free(file);
	file = NULL;
	return (file);
}

size_t	length_file(t_file *file)
{
	size_t size;
	t_file	*tmp;

	size = 0;
	tmp = file;
	while (file != NULL)
	{
		size++;
		file = file->next;
	}
	file = tmp;
	return (size);
}
