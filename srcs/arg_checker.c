/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:17:41 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 17:49:24 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_dir_or_file(char **argv)
{
	struct stat try_dirfile;
	int			i;

	i = -1;
	argv = order_by_lexic(argv);
	while (argv[++i])
		if (stat(argv[i], &try_dirfile) != -1)
		{
			if (S_ISDIR(try_dirfile.st_mode))
			{
				if ((g_global.lst_dir = insert_back_dir(g_global.lst_dir, argv[i], NULL)) == NULL)
					return (0);
			}
			else
			{

				if ((g_global.lst_file = insert_back_file(g_global.lst_file, &try_dirfile, argv[i])) == NULL)
					return (0);
			}
		}
		else
			no_such_error(argv[i]);
	return (1);
}

static int	fill_params(char *params)
{
	int i;

	i = 0;
	if (ft_strequ(params, "--"))
		return (0);
	while (params[i + 1])
	{
		if ((ft_strchr(ACCEPTED_PARAMS, params[i + 1])) != NULL)
			g_global.params |= ft_exp_l(2, ft_strclen(ACCEPTED_PARAMS, params[i + 1]));
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", params[i + 1]);
			ft_printf("usage: ft_ls [-%s] [file ...]\n", ACCEPTED_PARAMS);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (1);
}

int			arg_checker(int argc, char **argv)
{
	int		params_step;

	params_step = 0;
	if (argc < 2)
	{
		if ((g_global.lst_dir = insert_front_dir(g_global.lst_dir, "./", NULL)) == NULL)
			return (-1);
	}
	else
	{
		while (*(++argv) != NULL)
			if (((*argv)[0]) == '-' && ft_strlen(*argv) > 1 && params_step == 0)
			{
				if (fill_params(*argv) == 0)
					params_step = 1;
			}
			else
				break ;
		if (*argv != NULL)
			if (fill_dir_or_file(&(*argv)) == 0)
				return (0);
	}
	return (1);
}
