/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_01bis_parse_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:30:57 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:31:02 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Réalloue la mémoire nécessaire à l'implémentation d'un nouveau pipe
*/

int		ft_realloc_room_tab(t_room ***tab, t_room *room)
{
	t_room	**new;
	int		i;

	i = 0;
	if (*tab == NULL)
	{
		if (!(*tab = (t_room **)malloc(sizeof(t_room *) * 2)))
			return (ERROR);
		(*tab)[0] = room;
		(*tab)[1] = NULL;
		return (SUCCESS);
	}
	while ((*tab)[++i])
		;
	if (!(new = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
		return (ERROR);
	i = -1;
	while ((*tab)[++i])
		new[i] = (*tab)[i];
	new[i] = room;
	new[++i] = NULL;
	free(*tab);
	*tab = new;
	return (SUCCESS);
}

/*
**	Verfie que le nom de room associé au tube existe
**	Garanti le malloc des nouveaux tableaux de rooms
*/

int		ft_tube_aux(t_all *elem, t_room **tmp, t_room **cur)
{
	t_room ***matrice;

	if (*tmp == NULL || *cur == NULL)
		return (ERROR);
	if (ft_realloc_room_tab(&(*tmp)->tab, *cur) == ERROR)
		return (ERROR);
	if (ft_realloc_room_tab(&(*cur)->tab, *tmp) == ERROR)
		return (ERROR);
	if (elem->matrice_init == 0)
	{
		matrice = ft_init_matrice(elem->number_rooms);
		ft_set_matrice(tmp, cur, matrice);
		elem->matrice = matrice;
		elem->matrice_init = elem->matrice_init + 1;
	}
	else
	{
		matrice = elem->matrice;
//		ft_print_matrice(matrice, elem);
		ft_set_matrice(tmp, cur, matrice);
		elem->matrice = matrice;
	}
//	ft_print_matrice(elem->matrice, elem);
	return (SUCCESS);
}

/*
**	Appelé quand 1 seule str dans la ligne, qui ne commence pas par # et
**	qui contient '-'. Condition d'erreur ne permettant pas plus d'une
**	liaison (et qui suppose qu'une room ne peut pas contenir de '-'
**	si la room n existe pas tmp ou cur sera set a NULL et tube aux reverra une
**	erreur
*/

int		ft_tube(t_all *elem, char *line)
{
	t_room	*tmp;
	t_room	*cur;
	char	**tab_tube;
	int		i;

	i = 0;
	if (!(tab_tube = ft_strsplit(line, '-')))
		return (ERROR);
	while (tab_tube[++i])
		;
	if (i != 2)
		return (ERROR);
	tmp = elem->room;
	cur = elem->room;
	ft_find_room(&tmp, tab_tube[0]);
	ft_find_room(&cur, tab_tube[1]);
	if (ft_tube_aux(elem, &tmp, &cur) == ERROR)
		return (ft_error_tube(&tab_tube));
	i = -1;
	while (tab_tube[++i])
		free(tab_tube[i]);
	return (ft_free_them(1, tab_tube) ? SUCCESS : SUCCESS);
}

/*
**	Outil permettant simplement de verifier que les coordonnees des salles et
**	le nombre de fourmis tiennent bien dans un int
*/

int		ft_check_nb(char *s, int *nb)
{
	int			i;
	long long	long_nb;

	i = (s[0] == '-') ? 0 : -1;
	while (ft_isdigit(s[++i]) && s[i]);
	if (s[i] != '\0')
		return (ERROR);
	if (i > 12)
		return (ERROR);
	long_nb = ft_atol(s);
	if (long_nb > INT_MAX || long_nb < INT_MIN)
		return (ERROR);
	*nb = (int)long_nb;
	return (SUCCESS);
}

/*
**	Est appele pour la premiere ligne (hors commentaire)
**	utilise check_nb pour verifier que le nombre est bien un int
**	et ecrire a l'adresse elem->nb_ants la quantite de fourmies a envoyer
*/

int		ft_check_nb_ants(t_all *elem, char *str, int *i)
{
	if (str[0] == '#')
		return (SUCCESS);
	if (ft_check_nb(str, &elem->number_ants) == ERROR)
		return (ERROR);
	++(*i);
	return (SUCCESS);
}
