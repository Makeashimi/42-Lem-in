/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:08:52 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/19 21:26:12 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Verifier que le nombre de fourmis rentre dans un int ?
** Les salles sont-elles conformes ?
** Deux fois le meme nom de salles ?
** Deux fois le nombre de fourmis ?
** Pas de tube avant toutes les salles ?
** Les tubes sont-ils conformes ?
** Si la salle 1 c'est 0 0, la salle 2 c'est different de 0 0 ?
** 2147483647
*/

static t_ant	*create_link(char *str)
{
	t_ant	*ant;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		ft_error("Malloc error");
	if (!(ant->str = (char*)malloc(sizeof(char) * ft_strlen(str))))
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
	t_ant	*ant;
	t_room	*room;
	t_ant	*cpy;
	char	*str;
	int		ret;

	ret = 0;
	ant = NULL;
	room = NULL;
	while ((ret = get_next_line(1, &str)) == 1)
	{
		if (str[0] == '\0')
		{
			ft_strdel(&str);
			ft_error("ERROR : Non-conforming anthill");
		}
		ant = link_anthill(ant, str);
		ft_strdel(&str);
	}
	if (ret == -1)
		ft_error("Malloc error");
	if (ant == NULL)
		ft_error("ERROR : Anthill is empty");
	ant->nb = 0;
	cpy = ant;
	get_ant(ant);
	ft_printf("\nant->nb : %d\n", ant->nb);
	while (str_digit(cpy->str) == 0)
		cpy = cpy->next;
	cpy = cpy->next;
	find_room(cpy, room);
	/*while (ant != NULL)
	{
		ft_printf("%s\n", ant->str);
		ant = ant->next;
	}*/
	return (0);
}