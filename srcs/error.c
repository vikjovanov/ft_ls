/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:59:29 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 19:47:27 by vjovanov         ###   ########.fr       */
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

void	generic_error(const char *error_element)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(error_element);
}