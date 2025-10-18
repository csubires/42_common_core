/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinked_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:58:35 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 10:30:34 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLINKED_LIST_H
# define DLINKED_LIST_H

# include <stdlib.h>

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dllist;

t_dllist	*dlist_new(void *data);
t_dllist	*dlist_last(t_dllist *dllist);
void		dlist_add_before(t_dllist **dllist, t_dllist *new);
void		dlist_add_after(t_dllist **dllist, t_dllist *new);
void		dlist_clear(t_dllist **dllist, void (*del)(void*));
void		dlist_remove_before(t_dllist **dllist, void (*del)(void*));
void		dlist_remove(t_dllist **dllist, t_dllist *node, \
			void (*del)(void*));
size_t		dlist_has(t_dllist *dllist, t_dllist *node);
size_t		dlist_size(t_dllist *dlst);
void		dlist_free(void **node);

#endif
