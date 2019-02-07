/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_order_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 22:29:55 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 19:15:50 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*lst_order_reverse(t_file *lst_file)
{
	int		i;
	int		skip;
	int		length;
	t_file	*tmp;

	length = (int)length_file(lst_file);
	skip = 0;
	while (skip < length - 1)
	{
		i = -1;
		tmp = lst_file;
		while (++i < skip)
			tmp = tmp->next;
		lst_file = move_front_file(lst_file, tmp->next);
		skip++;
	}
	return (lst_file);
}

t_file	*lst_order_by_lexico(t_file *lst_file)
{
	t_file	*node_to_deplace;
	t_file	*tmp;
	int		skip;
	int		length;
	int		i;

	length = (int)length_file(lst_file);
	skip = 0;
	while (skip < length)
	{
		i = -1;
		tmp = lst_file;
		while (++i < skip)
			tmp = tmp->next;
		node_to_deplace = tmp;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->pathname, node_to_deplace->pathname) > 0)
				node_to_deplace = tmp;
			tmp = tmp->next;
		}
		lst_file = move_front_file(lst_file, node_to_deplace);
		skip++;
	}
	return (lst_file);
}

t_file	*lst_order_file(t_file *lst_file)
{
	if (!(PARAMS & PARAM_F))
	{
		if (PARAMS & PARAM_T)
			lst_file = lst_order_by_time(lst_file);
		else
			lst_file = lst_order_by_lexico(lst_file);
		if (PARAMS & PARAM_R)
			lst_file = lst_order_reverse(lst_file);
	}
	return (lst_file);
}
