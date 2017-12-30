/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:04 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/30 20:31:47 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

# define YELLOW "\033[38;5;228m"
# define ORANGE "\033[38;5;214m"
# define RED "\033[49;31m"
# define PURPLE "\033[49;35m"
# define BLUE "\033[49;34m"
# define GREEN "\033[33;32m"
# define EOC "\033[0m"

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
	int				close;
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
int					check_end(t_ant *ant, t_room *room);
void				init_path(t_room *room);
int					copy_last(t_ant *ant, t_room *room);
t_path				*get_smaller_path(t_room *room, char *str);


/*
** A SUPPRIMER !
*/

void	print_room(t_room *room);
void	print_path(t_path *path);
void	print_test(t_room *room);

#endif
