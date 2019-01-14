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

static int	check_quotes(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], ""))
		{
			opendir(argv[i]);
			ft_printf("ft_ls: fts_open: ");
			perror("");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	fill_dir_or_file(char **argv, char *params, t_dir *lst_dir)
{
	DIR *dir;
	struct stat try_file;

	if (check_quotes(argv))
		exit(EXIT_FAILURE);
	if ((dir = opendir(params)) != NULL)
	{
		if ((lst_dir = insert_back_dir(lst_dir, params, "./")) == NULL)
			return (0);
	}
	else
	{
		if (stat(params, &try_file) == -1)
		{
			ft_printf("ft_ls: %s: ", params);
			perror("");
		}
		//else
			//ECRIRE DANS STRUCT FICHIER
	}
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
			g_params |= ft_exp_l(2, ft_strclen(ACCEPTED_PARAMS, params[i + 1]));
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", params[i + 1]);
			ft_printf("usage: ft_ls [-%s] [file ...]\n", ACCEPTED_PARAMS);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	//ft_printf("%#b\n", g_params);
	return (1);
}

int			arg_checker(int argc, char **argv, t_dir *lst_dir)
{
	int		params_step;

	params_step = 0;
	if (argc < 2)
	{
		if ((lst_dir = insert_front_dir(lst_dir, "./", NULL)) == NULL)
			return (-1);
	}
	else
		while (*(++argv) != NULL)
			if (((*argv)[0]) == '-' && ft_strlen(*argv) > 1 && params_step == 0)
			{
				if (fill_params(*argv) == 0)
					params_step = 1;
			}
			else
			{
				fill_dir_or_file(argv, *argv, lst_dir);
				params_step = 1;
			}
	return (1);
}
