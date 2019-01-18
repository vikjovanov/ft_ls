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
** Definition of "extern t_global g_global" in header file
*/

t_global	g_global = {0, NULL, NULL};

int		main(int argc, char **argv)
{
	g_global.lst_dir = new_dir();
	g_global.lst_file = new_file();
	arg_checker(argc, argv);
	ft_printf("params : %#b\n\n", g_global.params);
	display_lst_dir(g_global.lst_dir);
	display_lst_file(g_global.lst_file);
	return (0);
}