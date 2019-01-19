/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 08:39:00 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/19 23:25:21 by vjovanov         ###   ########.fr       */
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
#include <errno.h>

#include "../libft/includes/libft.h"


#define PARAM_L 1
#define PARAM_R 2
#define PARAM_A 4
#define PARAM_RR 8
#define PARAM_T 16
#define ACCEPTED_PARAMS "lraRt"

typedef struct 		s_file 
{
	char			file_type;
	long			permission;
	int				number_of_link;
	char			*owner_name;
	char			*group_name;
	long			size_byte;
	time_t			modif_timestamps;
	char			*modif_month;
	char			*modif_day;
	char			*modif_hours;
	char			*modif_years;
	char			*pathname;
	struct s_file	*next;
}					t_file;

typedef struct 		s_dir 
{
	char			*parent;
	char			*pathname;
	struct s_dir	*next;
}					t_dir;

typedef struct 		s_field
{
	int				n_link;
	int				user_name;
	int				group_name;
	int				size_byte;
}					t_field;

/*
** char params
** bit 1 : -l
** bit 2 : -r
** bit 4 : -a
** bit 8 : -R
** bit 16: -t
*/

typedef struct 		s_global
{
	char			params;
	t_file			*lst_file;
	t_dir			*lst_dir;
}					t_global;

extern t_global g_global;

#define LST_DIR (g_global.lst_dir)
#define LST_FILE (g_global.lst_file)
#define PARAMS (g_global.params)


/*
** error
*/

void	no_such_error(const char *format);
void	generic_error(const char *error_element);

/*
** arg_checker
*/

int		arg_checker(int argc, char **argv);

/*
** generic_func
*/

long	ft_exp_l(long n, int exp);

/*
** lst_dir
*/

t_dir	*new_dir(void);
int		is_empty_dir(t_dir *dir);
t_dir	*insert_front_dir(t_dir *dir, char *path, char *parent);
t_dir	*insert_after_elem_dir(t_dir *dir, t_dir *ref_dir,
	char *path, char *parent);
t_dir	*insert_before_elem_dir(t_dir *dir, t_dir *ref_dir,
	char *path, char *parent);
t_dir	*insert_back_dir(t_dir *dir, char *path, char *parent);
t_dir	*del_back_dir(t_dir *dir);
t_dir	*del_front_dir(t_dir *dir);
t_dir	*clear_dir(t_dir *dir);
size_t	length_dir(t_dir *dir);

///////////////////////////////////////////////////////

void	display_lst_dir(t_dir *dir);

/*
** lst_file
*/

t_file	*new_file(void);
t_file	*insert_back_file(t_file *lst_file, struct stat *file, char *file_name);
void	display_lst_file(t_file *file);
int		is_empty_file(t_file *file);
t_file	*del_back_file(t_file *file);
t_file	*del_front_file(t_file *file);
t_file	*clear_file(t_file *file);
size_t	length_file(t_file *file);

/*
** order
*/

char		**order_by_lexic(char **str);

int		lst_order_file(t_file *lst_file);


/*
** print
*/

void	dispatch_print(t_file *lst_file, int print_mult_dir);







int		recurse_nav(void);

#endif