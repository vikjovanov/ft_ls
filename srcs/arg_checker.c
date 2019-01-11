/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:17:41 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/10 16:17:42 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
int		fill_dir(char **params_dir)
{
	int i;
	DIR *dir;

	i = 0;
	while (params_dir[i])
	{
		if ((dir = opendir(params_dir[i])) != NULL)

		i++;
	}
}
*/
int		fill_params(char *params)
{
	int i;

	i = 0;
	while (params[i])
	{
		if ((ft_strchr(ACCEPTED_PARAMS, params[i])) != NULL)
			g_params |= ft_exp_l(2, ft_strclen(ACCEPTED_PARAMS, params[i]));
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", params[i]);
			ft_printf("usage: ft_ls [-%s] [file ...]\n", ACCEPTED_PARAMS);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_printf("%#b\n", g_params);
	return (1);
}

int		arg_checker(int argc, char **argv, t_dir *lst_dir)
{
	if (argc < 2)
	{
		if (!(lst_dir = lstnew_dir("./", NULL)))
			return (-1);
	}
	else
	{
		if (argv[1][0] == '-')
			fill_params(&(argv[1][1]));
		/*if (argv[1][0] == '-' && argc > 2)
			fill_dir(&(argv[2]));
		else if (argv[1][0] != '-')
			fill_dir(&(argv[1]));*/
	}
	return (1);
}
