/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:04 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/19 21:25:14 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct		s_ant
{
	char			*str;
	long			nb;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_room
{
	char			*name;
	long			x;
	long			y;
	struct s_room	*next;
}					t_room;

void				get_ant(t_ant *ant);
void				find_room(t_ant *ant, t_room *room);
void				check_form(char *str);
void				check_content(t_room *room, char *str);

#endif
