/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_order_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 22:29:55 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 11:19:08 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
t_file	*lst_order_reverse(t_file *lst_file)
{

}

t_file	*lst_order_by_lexico(t_file *lst_file)
{

}
*/
t_file	*move_front_file(t_file *lst_file, t_file *element)
{
	t_file	*tmp;
	t_file	*previous;

	tmp = lst_file;
	//printf("DEBUT\n");
	//display_lst_file(lst_file);
	//printf("}}}}}}}}}}}}}}}}}}}}}\n");
	while (tmp != element)
	{
		//if (tmp == element)
		//	break ;
		previous = tmp;
		tmp = tmp->next;
	}
	//printf("elemet.next %p\n", element->next);
	previous->next = element->next;
	element->next = lst_file;
	//printf("%zu\n", length_file(element));
	//printf("APRES DEPLACEMENT\n");
	//display_lst_file(element);
	//printf("PPPPPPPPPPP\n");
	//exit(EXIT_FAILURE);
	return (element);
}

t_file	*find_last_block(t_file *lst_search)
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

t_file	*lst_order_by_lexicotime(t_file *lst_file)
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

t_file	*find_biggest_time(t_file *lst_search, int *swapped)
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


t_file	*lst_order_by_time(t_file *lst_file)
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
	printf("GO TO LEXICOTIME\n");
	lst_file = lst_order_by_lexicotime(lst_file);
	return (lst_file);
}

int		lst_order_file(t_file *lst_file)
{
	if (PARAMS & PARAM_T)
		lst_file = lst_order_by_time(lst_file);
	//else
		//tri par lexico
	//if (PARAMS & PARAMS_R)
		//tri par reverse
	//display_lst_file(lst_file);
	dispatch_print(lst_file, 0);
	return (1);
}