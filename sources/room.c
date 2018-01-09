/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 21:08:48 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 20:33:12 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			check_form(t_ant *ant, t_global *global, char *str)
{
	int		i;

	i = 0;
	if (str_nbr_i(str, ' ') != 2)
		error(ant, global, "Non-conforming room");
	if (str[i] == ' ')
		error(ant, global, "Non-conforming room2");
	while (str[i] != ' ')
		i++;
	i++;
	if (str[i] == ' ')
		error(ant, global, "Non-conforming room3");
	while (str[i] != ' ')
		i++;
	i++;
	if (str[i] == ' ' || str[i] == 0)
		error(ant, global, "Non-conforming room4");
}

static void		control_name_room(t_ant *ant, t_global *global, char *str)
{
	int		i;

	i = 0;
	if (str[0] == 'L')
		error(ant, global, "Non-conforming name of the room");
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			error(ant, global, "Non-conforming name of the room");
		i++;
	}
}

static void		control_coordinate(t_ant *ant, t_global *global, char *str)
{
	long	nb;

	if (str[0] == '-')
		error(ant, global, "Not accepting negative coordinate of the room");
	if (str_digit(str) == 0)
		error(ant, global, "Non-conforming coordinate of the room");
	if (ft_strlen(str) > 10)
		error(ant, global, "ERROR : Coordinate of the room is bigger than an integer");
	nb = ft_atol(str);
	if (nb > 2147483647)
		error(ant, global, "ERROR : Coordinate of the room is bigger than an integer");
}

void			check_content(t_ant *ant, t_global *global, t_room *room, char *str)
{
	//char	*tmp;
	char	*cpy;
	int		i;

	i = 0;
	//tmp = str;
	if (!(room->name = ft_strsub(str, 0, ft_strsrchi(str, ' '))))
		error(ant, global, "Malloc error");
	//free(tmp);
	control_name_room(ant, global, room->name);
	while (str[i] != ' ')
		i++;
	i++;
	if (!(cpy = (char*)malloc(sizeof(char) * ft_strlen(str))))
		error(ant, global, "Malloc error");
	cpy = strcpy_until(cpy, str + i, ' ');
	control_coordinate(ant, global, cpy);
	room->x = ft_atol(cpy);
	while (str[i] != ' ')
		i++;
	i++;
	cpy = strcpy_until(cpy, str + i, ' ');
	control_coordinate(ant, global, cpy);
	room->y = ft_atol(cpy);
	ft_strdel(&cpy);
}
