/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 09:23:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/08 09:23:11 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Definition of "extern char g_param" in header file
*/

t_global	global = {0, NULL, NULL};

int		main(int argc, char **argv)
{
	global.lst_dir = new_dir();
	global.lst_file = new_file();
	arg_checker(argc, argv);
	ft_printf("params : %#b\n\n", global.params);
	display_lst_dir(global.lst_dir);
	display_lst_file(global.lst_file);
	return (0);
}