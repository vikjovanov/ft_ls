/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:17:41 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 19:15:53 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_dir_or_file(char **argv, int *params_step,
	int (*stat)(const char*, struct stat*))
{
	struct stat try_dirfile;
	int			i;

	i = -1;
	argv = order_by_lexic(argv);
	*params_step = (*params_step == 0) ? 1 : *params_step;
	while (argv[++i] && (*params_step)++)
		if (stat(argv[i], &try_dirfile) != -1)
		{
			if (S_ISDIR(try_dirfile.st_mode))
			{
				if ((LST_DIR = insert_back_dir(LST_DIR, argv[i], NULL)) == NULL)
					return (0);
			}
			else
			{

				if ((LST_FILE = insert_back_file(LST_FILE, &try_dirfile, 
					argv[i], argv[i])) == NULL)
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
			PARAMS |= ft_exp_l(2, ft_strclen(ACCEPTED_PARAMS, params[i + 1]));
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
	argc = 2;
	while (*(++argv) != NULL)
		if (((*argv)[0]) == '-' && ft_strlen(*argv) > 1 && params_step == 0)
		{
			if (fill_params(*argv) == 0)
				params_step = 1;
		}
		else
			break ;
	if (*argv != NULL)
	{
		if (fill_dir_or_file(&(*argv), &params_step, (PARAMS & PARAM_L) ? &lstat : &stat) == 0)
			return (0);
		if (params_step > 2)
			return (2);
	}
	else
		if ((LST_DIR = insert_back_dir(LST_DIR, ".", NULL)) == NULL)
			return (0);
	return (1);
}
