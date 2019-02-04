/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 09:23:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 21:25:11 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Definition of "extern t_global g_global" in header file
*/

t_global	g_global = {0, NULL, NULL};

int		main(int argc, char **argv)
{
	int		multi_dir;
	int		res;

	LST_DIR = new_dir();
	LST_FILE = new_file();
	multi_dir = 0;
	if ((res = arg_checker(argc, argv)) == 0)
		exit_failure();
	else if (res == 2)
		multi_dir = 1;
	//display_lst_file(LST_FILE);
	if (!(is_empty_file(LST_FILE)))
		dispatch_print(LST_FILE, 2);
	//display_lst_dir(LST_DIR);
	while (!is_empty_dir(LST_DIR))
	{
		LST_FILE = new_file();
		if (!(recurse_nav()))
			
		//display_lst_file(LST_FILE);
		//display_lst_dir(LST_DIR);
		LST_FILE = lst_order_file(LST_FILE);
		if (PARAMS & PARAM_RR)
			LST_DIR = fill_lst_dir(LST_FILE, LST_DIR);		
		LST_FILE = dispatch_print(LST_FILE, multi_dir);
		LST_DIR = del_front_dir(LST_DIR);
		ft_memdel((void**)&(LST_FILE));
		multi_dir = ((PARAMS & PARAM_RR) ? 1 : 0);
	}
	return (0);
}