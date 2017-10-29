/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:04 by jcharloi          #+#    #+#             */
/*   Updated: 2017/10/29 18:48:33 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

typedef struct		s_ant
{
	char			*str;
	int				nb;
	char			*start;
	char			*end;
	struct s_ant	*next;
}					t_ant;

void				get_ant(t_ant *ant);
void				get_start(t_ant *ant);
void				get_end(t_ant *ant);