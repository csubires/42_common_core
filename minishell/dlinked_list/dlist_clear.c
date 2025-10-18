/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:03:30 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 10:25:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_clear(t_dllist **dllist, void (*del)(void*))
{
	if (dllist)
		while (*dllist)
			dlist_remove_before(dllist, del);
}
