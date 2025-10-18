/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_has.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:04:59 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 10:30:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

size_t	dlist_has(t_dllist *dllist, t_dllist *node)
{
	t_dllist	*tmp_list;

	tmp_list = dllist;
	while (tmp_list)
	{
		if (tmp_list == node)
			return (1);
		tmp_list = tmp_list->next;
	}
	return (0);
}
