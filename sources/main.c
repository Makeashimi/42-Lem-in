/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:08:52 by jcharloi          #+#    #+#             */
/*   Updated: 2017/10/29 18:49:04 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	is_conforme(t_ant *ant)
{
	
}

t_ant	*create_link(char *str)
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

t_ant	*link_link(t_ant *ant, char *str)
{
	t_ant *tmp = ant;

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

int		main(void)
{
	t_ant	*ant;
	char	*str;
	int		ret;

	ret = 0;
	ant = NULL;
	while ((ret = get_next_line(1, &str)) == 1)
	{
		if (str[0] == '\0')
		{
			ft_strdel(&str);
			ft_error("ERROR : Non-conforming anthill");
		}
		ant = link_link(ant, str);
		ft_strdel(&str);
	}
	if (ret == -1)
		ft_error("Malloc error");
	ant->nb = 0;
	get_ant(ant);
	ft_printf("\nant->nb : %d\n", ant->nb);
	get_start(ant);
	ft_printf("ant->start : %s\n", ant->start);
	get_end(ant);
	ft_printf("ant->end : %s\n", ant->end);
	is_conforme(ant);
	/*while (ant != NULL)
	{
		ft_printf("%s\n", ant->str);
		ant = ant->next;
	}*/
	return (0);
}
