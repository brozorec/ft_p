/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:40:32 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 18:25:09 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/socket.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/mman.h>
# include "../libft/includes/libft.h"
# include "get_next_line.h"

void		err_msg(char *err);
void		fatal(char *str);
void		close_connection(int cfd);
void		do_interaction(int cfd);
char		*receive_msg(int cfd);
int			send_msg(char *buff, int cfd);
void		receive_file(int cfd, char *name);
void		send_file(int cfd, char *buff);

#endif
