/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_by.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:59:01 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/17 15:59:02 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_swapp(char **str1, char **str2)
{
	char *tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

char		**order_by_lexic(char **str)
{
	int		ordered;
	int		i;

	ordered = 0;
	while (ordered != 1)
	{
		i = 0;
		ordered = 1;
		while (str[i])
		{
			if (str[i + 1] == NULL)
				break ;
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				ft_swapp(&(str[i]), &(str[i + 1]));
				ordered = 0;
			}
			i++;
		}
	}
	return (str);
}