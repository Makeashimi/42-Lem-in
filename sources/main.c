/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:08:52 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/08 20:33:18 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant	*create_link(char *str)
{
	t_ant	*ant;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		ft_error("Malloc error");
	ft_memset(ant, 0, sizeof(t_ant));
	if (!(ant->str = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ft_error("Malloc error");
	ant->str = ft_strcpy(ant->str, str);
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

static void		next(t_global *global, t_ant *ant)
{
	t_ant		*cpy;

	cpy = ant;
	get_ant(ant);
	while (str_digit(cpy->str) == 0)
		cpy = cpy->next;
	cpy = cpy->next;
	cpy = find_room(global, cpy, NULL);
	check_pipe(global, cpy, NULL);
	cpy = ant;
	get_start(ant, cpy);
	get_end(ant, cpy);
	compare_room(global);
	compare_pipe(global);
	start_algo(global, ant);
	cpy = ant;
	while (cpy != NULL)
	{
		ft_printf("%s\n", cpy->str);
		cpy = cpy->next;
	}
	ft_printf("\n");
	if (start_end_linked(ant) == 0)
		begin_ant(ant, 1, 1, ant->len - 1);
	ft_printf("\n");
}

int				main(void)
{
	t_ant		*ant;
	t_global	*global;
	char		*str;
	int			ret;

	ant = NULL;
	if (!(global = (t_global*)malloc(sizeof(t_global))))
		ft_error("Malloc error");
	ft_memset(global, 0, sizeof(t_global));
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
	next(global, ant);
	return (0);
}
