/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 11:35:46 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/11 11:35:47 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_empty_dir(t_dir *dir)
{
	if (dir == NULL)
		return (1);
	return (0);
}
/*
t_dir	*del_back_dir(t_dir *dir)
{

}

t_dir	*del_front_dir(t_dir *dir)
{

}

t_dir	*clear_dir(t_dir *dir)
{

}

size_t	*length_dir(t_dir *dir)
{

}
*/