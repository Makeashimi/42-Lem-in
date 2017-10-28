/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:08:52 by jcharloi          #+#    #+#             */
/*   Updated: 2017/10/28 19:20:53 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** -------------- PARSING DU NOMBRE DE FOURMIS -------------------
** Il peut y avoir des '#commentaire' avant le nombre de fourmis
** le premier caractere different en dessous DOIT etre le nb de fourmis
** Cas d'erreurs : 	- ## \n
**					- Un espace \n
**					- Autre chose qu'un seul nombre sur la 'bonne ligne'
**
*/

void	get_ant(t_ant *ant)
{
	t_ant	*tmp;
	int		i;

	i = 0;
	tmp = ant;
	while (tmp != NULL && tmp->str[0] == '#' && tmp->str[1] != '#')
		tmp = tmp->next;
	if (tmp == NULL)
		ft_error("ERROR : No ants");
	if (ft_isdigit(tmp->str[0]))
	{
		while (tmp->str[i] != '\0')
		{
			if (ft_isdigit(tmp->str[i]) == 0)
				ft_error("ERROR : Non-conforming anthill");
			i++;
		}
		ant->nb = ft_atoi(tmp->str);
	}
	else
		ft_error("ERROR : Non-conforming anthill");
	if (ant->nb < 1)
		ft_error("ERROR : Wrong number of ants");
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
	ft_printf("ant->nb : %d\n", ant->nb);
	/*while (ant != NULL)
	{
		ft_printf("%s\n", ant->str);
		ant = ant->next;
	}*/
	return (0);
}
