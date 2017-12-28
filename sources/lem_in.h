/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:04 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/28 19:36:39 by jcharloi         ###   ########.fr       */
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
	struct s_ant	*next;
}					t_ant;

/*
** Special structures for room and pipe
*/

typedef struct		s_path
{
	int				distance;
	char			*from;
	struct s_path	*next;
}					t_path;

typedef struct		s_room
{
	char			*name;
	long			x;
	long			y;
	t_path			*path;
	struct s_room	*next;
}					t_room;

typedef struct		s_pipe
{
	char			*s1;
	char			*s2;
	struct s_pipe	*next;
}					t_pipe;

/*
** Global structure to get everything
*/

typedef struct		s_global
{
	t_room			*room;
	t_pipe			*pipe;
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
t_path				*link_path(t_path *path);

#endif
