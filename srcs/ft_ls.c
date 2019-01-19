/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 09:23:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 17:51:06 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Definition of "extern t_global g_global" in header file
*/

t_global	g_global = {0, NULL, NULL};

int		main(int argc, char **argv)
{
	g_global.lst_dir = new_dir();
	g_global.lst_file = new_file();
	if (!(arg_checker(argc, argv)))
		exit(EXIT_FAILURE);
	//ft_printf("params : %#b\n\n", g_global.params);
	//display_lst_dir(g_global.lst_dir);
	//display_lst_file(g_global.lst_file);
	dispatch_print(g_global.lst_file, 0);
	return (0);
}