/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 08:39:00 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/08 08:39:01 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h> 
#include <stdio.h>
#include <string.h>

#include "../libft/includes/libft.h"

typedef struct 		s_file 
{
	char			file_mode;
	short			permission;
	int				number_of_link;
	char			*owner_name;
	char			*group_name;
	long			size_byte;
	char			*last_modif_month;
	char			*last_modif_day;
	char			*last_modif_hour;
	char			*last_modif_minute;
	char			*pathname;
	struct s_file	*next;
}					t_file;

int		display_dir(char *pathname);

#endif