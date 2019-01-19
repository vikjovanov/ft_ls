/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_order_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 22:29:55 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 23:33:57 by vjovanov         ###   ########.fr       */
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
	while (tmp != element)
	{
		if (tmp == element)
			break ;
		previous = tmp;
		tmp = tmp->next;
	}
	previous->next = lst_file->next;
	element->next = tmp;
	return (element);
}

t_file	*lst_order_by_time(t_file *lst_file)
{
	t_file	*node_to_deplace;
	t_file	*tmp;
	int		swapped;

	// on part sur l'idee de deplacer le plus grand q chaque tour au debut de la liste
	swapped = 1;
	while (swapped)
	{
		tmp = lst_file;
		node_to_deplace = lst_file;
		swapped = 0;
		while (tmp != NULL)
		{
			if (tmp->modif_timestamps > node_to_deplace->modif_timestamps)
			{
				node_to_deplace = tmp;
				swapped = 1;
			}
			tmp = tmp->next;
		}
		if (swapped)
		{
			printf("p\n");
			lst_file = move_front_file(lst_file, node_to_deplace);
			printf("q\n");
		}
	//display_lst_file(lst_file);

	}
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
	display_lst_file(lst_file);
	return (1);
}