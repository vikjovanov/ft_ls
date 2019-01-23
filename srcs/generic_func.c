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

char	*quadruple_join(char *str1, char *str2, char *str3, char *str4)
{
	char *tmp;
	char *new;

	tmp = NULL;
	new = NULL;
	if (str1 == NULL || str2 == NULL || str3 == NULL || str4 == NULL)
		return (NULL);
	new = ft_strjoin(str1, str2);
	tmp = ft_strjoin(new, str3);
	ft_memdel((void**)&new);
	new = ft_strjoin(tmp, str4);
	ft_memdel((void**)&tmp);
	return (new);
}

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