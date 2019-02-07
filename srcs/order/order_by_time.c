/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_by_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 11:46:22 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 19:13:59 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*find_last_block(t_file *lst_search)
{
	t_file	*last_block;

	last_block = lst_search;
	while (lst_search != NULL)
	{
		if (lst_search->modif_timestamps < last_block->modif_timestamps)
			last_block = lst_search;
		lst_search = lst_search->next;
	}
	return (last_block);
}

static t_file	*lst_order_by_lexicotime(t_file *lst_file)
{
	t_file	*last_block;
	t_file	*tmp;
	t_file	*node_to_deplace;
	int		skip;
	int		i;

	skip = 0;
	while (skip != (int)length_file(lst_file))
	{
		i = -1;
		tmp = lst_file;
		while (++i != skip)
			tmp = tmp->next;
		last_block = find_last_block(tmp);
		node_to_deplace = last_block;
		while (last_block != NULL)
		{
			if (ft_strcmp(last_block->pathname, node_to_deplace->pathname) > 0)
				node_to_deplace = last_block;
			last_block = last_block->next;
		}
		lst_file = move_front_file(lst_file, node_to_deplace);
		skip++;
	}
	return (lst_file);
}

static t_file	*find_biggest_time(t_file *lst_search, int *swapped)
{
	t_file	*node_to_deplace;

	node_to_deplace = lst_search;
	while (lst_search != NULL)
	{
		if (lst_search->modif_timestamps <= node_to_deplace->modif_timestamps)
		{
			node_to_deplace = lst_search;
			*swapped = 1;
		}
		lst_search = lst_search->next;
	}
	return (node_to_deplace);
}

t_file			*lst_order_by_time(t_file *lst_file)
{
	t_file	*node_to_deplace;
	t_file	*tmp;
	int		swapped;
	int		skip;
	int		i;

	swapped = 1;
	skip = 0;
	while (swapped)
	{
		tmp = lst_file;
		swapped = 0;
		i = -1;
		while (++i != skip)
			tmp = tmp->next;
		node_to_deplace = find_biggest_time(tmp, &swapped);
		if (swapped)
		{
			lst_file = move_front_file(lst_file, node_to_deplace);
			skip++;
		}
	}
	lst_file = lst_order_by_lexicotime(lst_file);
	return (lst_file);
}
