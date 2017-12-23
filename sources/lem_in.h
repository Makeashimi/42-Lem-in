/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:04 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/23 22:40:19 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct		s_ant
{
	char			*str;
	long			nb;
	char			*start;
	char			*end;
	char			*here;
	int				i;
	int				boucle;
	int				*tab;
	struct s_ant	*next;
}					t_ant;

/*
** Special structures for room and pipe
*/

typedef struct		s_room
{
	char			*name;
	long			x;
	long			y;
	struct s_room	*next;
}					t_room;

typedef struct		s_pipe
{
	char			*s1;
	char			*s2;
	struct s_pipe	*next;
}					t_pipe;

/*
** Get the path and the pathcpy
*/

typedef struct 		s_path
{
	char			*str;
	struct s_path	*next;
}					t_path;

typedef struct 		s_lst
{
	t_path			*path;
	struct s_lst	*next;
}					t_lst;

/*
** Global structure to get everything
*/

typedef struct		s_global
{
	t_room			*room;
	t_pipe			*pipe;
	t_lst			*lst;
}					t_global;

/*
** Fonctions used for parsing
*/

void				get_ant(t_ant *ant);
t_ant				*find_room(t_global *global, t_ant *ant, t_room *room);
void				check_form(char *str);
void				check_content(t_room *room, char *str);
int					find_pipe(char *str);
void				check_pipe(t_global *global, t_ant *cpy, t_pipe *pipe);
void				get_start(t_ant *ant, t_ant *cpy);
void				get_end(t_ant *ant, t_ant *cpy);
void				compare_room(t_global *global);
void				compare_pipe(t_global *global);
int					is_pipe(t_pipe *pipe, char *str);

/*
** Fonctions used for the real algo
*/

void				start_algo(t_global *global, t_ant *ant);
void				init_tab(t_pipe *pipe, t_ant *ant);
int					tube_len(t_pipe *pipe);
void				get_paths(t_global *global, t_ant *ant);
int					check_tab_zero(t_global *global, int *tab);
t_lst				*link_lst(t_lst **lst);
t_path				*link_path(t_lst *lst);
void				save_path(t_lst *lst, char *here);
t_lst				*previous_lst(t_lst *lst);
char				*move_back(t_global *global, t_lst *lst, t_ant *ant);
void				copy_path(t_lst *previous, t_lst *end);
int					cmp_lst(t_lst *lst, char *here);
int					cmp_path(t_pipe *tmp, t_ant *ant);
void				show_paths(t_global *global);

#endif
