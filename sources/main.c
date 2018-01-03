/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:08:52 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/03 12:41:04 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant	*create_link(char *str)
{
	t_ant	*ant;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		ft_error("Malloc error");
	if (!(ant->str = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ft_error("Malloc error");
	ant->str = ft_strcpy(ant->str, str);
	ant->next = NULL;
	return (ant);
}

static t_ant	*link_anthill(t_ant *ant, char *str)
{
	t_ant *tmp;

	tmp = ant;
	if (tmp == NULL)
	{
		ant = create_link(str);
		return (ant);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_link(str);
	return (ant);
}

int				main(void)
{
	t_ant		*ant;
	t_ant		*cpy;
	t_room		*room;
	t_pipe		*pipe;
	t_global 	*global;
	t_path		*path;
	char		*str;
	int			ret;

	ret = 0;
	ant = NULL;
	room = NULL;
	pipe = NULL;
	path = NULL;
	if (!(global = (t_global*)malloc(sizeof(t_global))))
		ft_error("Malloc error");
	global->room = NULL;
	global->pipe = NULL;
 	while ((ret = get_next_line(0, &str)) == 1)
	{
		if (str[0] == '\0')
		{
			ft_strdel(&str);
			break ;
		}
		ant = link_anthill(ant, str);
		ft_strdel(&str);
	}
	if (ret == -1)
		ft_error("Malloc error");
	if (ant == NULL)
		ft_error("ERROR : Anthill is empty");
	ant->here = NULL;
	cpy = ant;
	get_ant(ant);
	//ft_printf("\nant->nb : %d\n", ant->nb);
	while (str_digit(cpy->str) == 0)
		cpy = cpy->next;
	cpy = cpy->next;
	cpy = find_room(global, cpy, room);
	/*while (global->room != NULL)
	{
		ft_printf("global->room->name : %s ", global->room->name);
		ft_printf("global->room->x : %d ", global->room->x);
		ft_printf("global->room->y : %d\n", global->room->y);
		global->room = global->room->next;
	}*/
	check_pipe(global, cpy, pipe);
	/*while (global->pipe != NULL)
	{
		ft_printf("global->pipe->s1 : %s ", global->pipe->s1);
		ft_printf("global->pipe->s2 : %s\n", global->pipe->s2);
		global->pipe = global->pipe->next;
	}*/
	cpy = ant;
	get_start(ant, cpy);
	//ft_printf("start : %s\n", ant->start);
	get_end(ant, cpy);
	//ft_printf("end : %s\n", ant->end);
	compare_room(global);
	compare_pipe(global);
	start_algo(global, ant);
	/*while (ant != NULL)
	{
		ft_printf("%s\n", ant->str);
		ant = ant->next;
	}*/
	return (0);
}
