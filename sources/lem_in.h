/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:04 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/25 21:09:00 by jcharloi         ###   ########.fr       */
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
	struct s_ant	*next;
}					t_ant;

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

typedef struct		s_global
{
	t_room			*room;
	t_pipe			*pipe;
}					t_global;

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

#endif
