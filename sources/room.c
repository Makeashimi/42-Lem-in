/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 21:08:48 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/24 16:54:51 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			check_form(char *str)
{
	int		i;

	i = 0;
	if (str_nbr_i(str, ' ') != 2)
		ft_error("Non-conforming room");
	if (str[i] == ' ')
		ft_error("Non-conforming room");
	while (str[i] != ' ')
		i++;
	i++;
	if (str[i] == ' ')
		ft_error("Non-conforming room");
	while (str[i] != ' ')
		i++;
	i++;
	if (str[i] == ' ' || str[i] == 0)
		ft_error("Non-conforming room");
}

static void		control_name_room(char *str)
{
	int		i;

	i = 0;
	if (str[0] == 'L')
		ft_error("Non-conforming name of the room");
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			ft_error("Non-conforming name of the room");
		i++;
	}
}

static void		control_coordinate(char *str)
{
	long	nb;

	if (str[0] == '-')
		ft_error("Not accepting negative coordinate of the room");
	if (str_digit(str) == 0)
		ft_error("Non-conforming coordinate of the room");
	if (ft_strlen(str) > 10)
		ft_error("ERROR : Coordinate of the room is bigger than an integer");
	nb = ft_atol(str);
	if (nb > 2147483647)
		ft_error("ERROR : Coordinate of the room is bigger than an integer");
}

void			check_content(t_room *room, char *str)
{
	char	*cpy;
	int		i;

	i = 0;
	room->name = ft_strsub(str, 0, ft_strsrchi(str, ' '));
	control_name_room(room->name);
	while (str[i] != ' ')
		i++;
	i++;
	if (!(cpy = (char*)malloc(sizeof(char) * ft_strlen(str))))
		ft_error("Malloc error");
	cpy = strcpy_until(cpy, str + i, ' ');
	control_coordinate(cpy);
	room->x = ft_atol(cpy);
	while (str[i] != ' ')
		i++;
	i++;
	cpy = strcpy_until(cpy, str + i, ' ');
	control_coordinate(cpy);
	room->y = ft_atol(cpy);
	ft_strdel(&cpy);
}
