/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:20 by csubires          #+#    #+#             */
/*   Updated: 2024/10/12 11:37:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

t_dllist	*dlist_last(t_dllist *dllist)
{
	t_dllist	*tmp_list;

	if (!dllist)
		return (0);
	tmp_list = dllist;
	while (tmp_list->next)
		tmp_list = tmp_list->next;
	return (tmp_list);
}
