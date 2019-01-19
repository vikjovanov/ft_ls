/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 09:23:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 23:25:41 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Definition of "extern t_global g_global" in header file
*/

t_global	g_global = {0, NULL, NULL};

int		main(int argc, char **argv)
{
	LST_DIR = new_dir();
	LST_FILE = new_file();
	if (!(arg_checker(argc, argv)))
		exit(EXIT_FAILURE);
	if (!(is_empty_file(LST_FILE)))
		dispatch_print(LST_FILE, 1);
	recurse_nav();
	lst_order_file(LST_FILE);
	//dispatch_print(LST_FILE, 1);
	//ft_printf("params : %#b\n\n", g_global.params);
	//display_lst_dir(g_global.lst_dir);
	//display_lst_file(g_global.lst_file);
	
	return (0);
}