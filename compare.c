/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:11:48 by vjovanov          #+#    #+#             */
/*   Updated: 2019/02/06 15:11:51 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>


int		main(int argc, char **argv)
{
	char *tmp;
	char *command;

	if (argc < 2)
		return (0);
	tmp = ft_strjoin("ls ", argv[1]);
	command = ft_strjoin(tmp, " > ls.txt");
	free(tmp);
	if (system(command) >= 0)
		ft_printf("{bold}ls : {green}OK{eoc}{eocbold}\n");
	else
	{
		ft_printf("{bold}ls : {red}ERROR{eoc}{eocbold}\n");
		exit(EXIT_FAILURE);
	}
	free(command);
	tmp = ft_strjoin("./ft_ls ", argv[1]);
	command = ft_strjoin(tmp, " > ft_ls.txt");
	if (system(command) >= 0)
		ft_printf("{bold}ft_ls : {green}OK{eoc}{eocbold}\n");
	else
	{
		ft_printf("{bold}ft_ls : {red}ERROR{eoc}{eocbold}\n");
		exit(EXIT_FAILURE);
	}

	int fd1 = open("ls.txt", O_RDONLY);
	int fd2 = open("ft_ls.txt", O_RDONLY);
	char *line1;
	char *line2;
	long long error, line;

	error = 0;
	line = 0;
	line1 = NULL;
	line2 = NULL;
	while (get_next_line(fd1, &line1) == 1)
	{
		if (get_next_line(fd2, &line2) == 1)
		{
			if (!ft_strequ(line1, line2))
			{
				ft_printf("%ld |ls   | %s\n", line, line1);
				ft_printf("%ld |ft_ls| %s\n", line, line2);
				ft_printf("\n");
				error++;
			}
			free(line1);
			free(line2);
		}
		line++;
	}
	if (error != 0)
		ft_printf("{bold}{red}%lld différence detectée{eoc}{eocbold}\n", error);
	else
		ft_printf("{bold}{green}Aucune différence detectée{eoc}{eocbold}\n", error);
	return (0);
}