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

char g_params = 0;



int		main(int argc, char **argv)
{
	t_dir	*lst_dir;

	lst_dir = NULL;
	arg_checker(argc, argv, lst_dir);
	return (0);
}