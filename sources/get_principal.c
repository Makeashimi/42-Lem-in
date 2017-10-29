/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_principal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:47:09 by jcharloi          #+#    #+#             */
/*   Updated: 2017/10/29 18:48:13 by jcharloi         ###   ########.fr       */
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
** VERIFIER QUE Y A PAS DEUX FOIS L'UN DES TROIS PARAMÈTRES À RECUPÉRER
**
** --------------------- PARSING DES SALLES ----------------------
** Une salle ne commencera jamais par le caractère L ou le caractère #
** elle peut avoir un nom très diversifié
** Cas d'erreurs :  - ## entre le start et la ligne supposée etre la salle
**					- Pas de coordonnées après ou mal écrites
**					- 
*/

void	get_ant(t_ant *ant)
{
	t_ant	*tmp;

	tmp = ant;
	while (tmp != NULL && tmp->str[0] == '#' && tmp->str[1] != '#')
		tmp = tmp->next;
	if (tmp == NULL)
		ft_error("ERROR : No ants");
	if (ft_isdigit(tmp->str[0]))
	{
		if (str_digit(tmp->str))
			ant->nb = ft_atoi(tmp->str);
		else
			ft_error("ERROR : Non-conforming anthill");
	}
	else
		ft_error("ERROR : No ants");
	if (ant->nb < 1)
		ft_error("ERROR : Wrong number of ants");
}

void	get_start(t_ant *ant)
{
	t_ant	*tmp;

	tmp = ant;
	while (tmp != NULL && ft_strcmp(tmp->str, "##start") != 0)
		tmp = tmp->next;
	if (tmp->str == NULL)
		ft_error("ERROR : No start room");
	if (ft_strcmp(tmp->str, "##start") == 0)
	{
			tmp = tmp->next;
			while (tmp != NULL && tmp->str[0] == '#' && tmp->str[1] != '#')
				tmp = tmp->next;
			if (tmp == NULL || (tmp->str[0] == '#' && tmp->str[1] == '#') || tmp->str[0] == 'L')
				ft_error("ERROR : Non-conforming anthill");
			else
			{
				if (ft_strsrchi(tmp->str, ' ') == -1)
					ft_error("Non-conforming anthill");
				if(!(ant->start = (char*)malloc(sizeof(char) * ft_strlen(tmp->str))))
					ft_error("Malloc error");
				ant->start = strcpy_until(ant->start, tmp->str, ' ');
				return ;
			}
	}
	else
		ft_error("ERROR : No start room");
}

void	get_end(t_ant *ant)
{
	t_ant	*tmp;

	tmp = ant;
	while (tmp != NULL && ft_strcmp(tmp->str, "##end") != 0)
		tmp = tmp->next;
	if (tmp->str == NULL)
		ft_error("ERROR : No end room");
	if (ft_strcmp(tmp->str, "##end") == 0)
	{
			tmp = tmp->next;
			while (tmp != NULL && tmp->str[0] == '#' && tmp->str[1] != '#')
				tmp = tmp->next;
			if (tmp == NULL || (tmp->str[0] == '#' && tmp->str[1] == '#') || tmp->str[0] == 'L')
				ft_error("ERROR : Non-conforming anthill");
			else
			{
				if (ft_strsrchi(tmp->str, ' ') == -1)
					ft_error("Non-conforming anthill");
				if(!(ant->end = (char*)malloc(sizeof(char) * ft_strlen(tmp->str))))
					ft_error("Malloc error");
				ant->end = strcpy_until(ant->end, tmp->str, ' ');
				return ;
			}
	}
	else
		ft_error("ERROR : No end room");
}
