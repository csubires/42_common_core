/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesumore <jesumore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:04:22 by csubires          #+#    #+#             */
/*   Updated: 2024/11/30 14:31:30 by jesumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_remove(t_dllist **dllist, t_dllist *node, void (*del)(void*))
{
	if (dllist && *dllist && node && dlist_has(*dllist, node))
	{
		if (node == *dllist)
			dlist_remove_before(dllist, del);
		else
		{
			if (node->prev)
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			del(node->data);
			free(node);
			node = 0;
		}
	}
}
