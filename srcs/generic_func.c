/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 09:10:14 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/11 09:10:16 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	ft_exp_l(long n, int exp)
{
	long	value_exp;
	int		i;

	value_exp = n;
	i = 0;
	if (exp == 0)
		return (1.0);
	while (i < exp - 1)
	{
		value_exp *= n;
		i++;
	}
	return (value_exp);
}

void	exit_failure(void)
{
	clear_dir(LST_DIR);
	clear_file(LST_FILE);
	generic_error("Abort");
	exit(EXIT_FAILURE);
}