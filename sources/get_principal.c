/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_principal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:47:09 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 20:02:40 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** 2147483647
** -------------- PARSING DU NOMBRE DE FOURMIS -------------------
** Il peut y avoir des '#commentaire' avant le nombre de fourmis
** le premier caractere different en dessous DOIT etre le nb de fourmis
** Cas d'erreurs : 	- Autre chose qu'un nombre
**					- Nombre superieur à un int
**
** VERIFIER QUE Y A PAS DEUX FOIS L'UN DES TROIS PARAMÈTRES À RECUPÉRER
**
** --------------------- PARSING DES SALLES ----------------------
** Une salle ne commencera jamais par le caractère L ou le caractère #
** elle peut avoir un nom très diversifié
** Cas d'erreurs :  - ## entre le start et la ligne supposée etre la salle
**					- Pas plus/pas moins de 2 espaces
**                  - Un caractere avant chaque espace
**					- Un 0 apres le deuxieme espace
**					- Un L devant le nom/de - dans le nom
**					- Coordonnees negatives/superieures à un int
**
** -------------------- PARSING DES TUBES -----------------------
** Relie des salles avec un '-' au milieu
** Cas d'erreurs :  - Un espace ou un - en str[0]
**					- Pas de -
**					- Un 0 apres le -
*/

static t_room	*create_room(t_ant *ant, t_global *global)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		error(ant, global, "Malloc error");
	ft_memset(room, 0, sizeof(t_room));
	return (room);
}

static t_room	*link_room(t_room *room, t_ant *ant, t_global *global)
{
	t_room *tmp;

	tmp = room;
	if (tmp == NULL)
	{
		room = create_room(ant, global);
		return (room);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_room(ant, global);
	return (room->next);
}

t_ant			*find_room(t_global *global, t_ant *cpy, t_room *room, t_ant *ant)
{
	if (cpy == NULL)
		error(ant, global, "No room");
	while (cpy != NULL && find_pipe(cpy->str) == 0)
	{
		while (cpy != NULL && cpy->str[0] == '#')
			cpy = cpy->next;
		if (cpy == NULL)
			error(ant, global, "No room or no pipe");
		if (find_pipe(cpy->str) == 1)
			break ;
		room = link_room(room, ant, global);
		if (global->room == NULL)
			global->room = room;
		check_form(ant, global, cpy->str);
		check_content(ant, global, room, cpy->str);
		cpy = cpy->next;
	}
	if (global->room == NULL)
		error(ant, global, "No room");
	return (cpy);
}

void			get_ant(t_ant *ant, t_global *global)
{
	t_ant	*tmp;

	tmp = ant;
	while (tmp != NULL && tmp->str[0] == '#')
		tmp = tmp->next;
	if (tmp != NULL && ft_isdigit(tmp->str[0]))
	{
		if (str_digit(tmp->str) == 1)
		{
			if (ft_strlen(tmp->str) > 10)
				error(ant, global, "ERROR : Number of ants is bigger than an integer");
			else
				ant->nb = ft_atol(tmp->str);
		}
		else
			error(ant, global, "ERROR : Non-conforming number of ants");
	}
	else
		error(ant, global, "ERROR : No ants or non-conforming number of ants");
	if (ant->nb > 2147483647)
		error(ant, global, "ERROR : Number of ants is bigger than an integer");
	if (ant->nb < 1)
		error(ant, global, "ERROR : Wrong number of ants");
}
