/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 16:57:39 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/07 18:02:30 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include "./libft/includes/libft.h"

typedef struct			s_struct
{
	int					index;
	char				*content;
	struct s_struct		*next;
}						t_struct;

int						get_next_line(int const fd, char **line);

#endif
