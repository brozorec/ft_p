/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:42 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/06 19:32:30 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <sys/socket.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/wait.h>
# include "./libft/includes/libft.h"
# include "get_next_line.h"

void		err_msg(char *err);
void		usage(char *str);
int 		get_next_line(int fd, char **line);

#endif
