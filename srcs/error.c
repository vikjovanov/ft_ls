/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:59:29 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/17 19:59:30 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	no_such_error(const char *name_error)
{
	if (ft_strequ(name_error, ""))
		name_error = "fts_open";
	ft_putstr_fd("ft_ls: ", 2);
	perror(name_error);
	if (ft_strequ(name_error, "fts_open"))
		exit(EXIT_FAILURE);
}
