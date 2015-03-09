/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:42 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/07 18:35:10 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/mman.h>
# include "../libft/includes/libft.h"
# include "get_next_line.h"

void		err_msg(char *err);
void		usage(char *str);
int 		get_next_line(int fd, char **line);
void		do_ls(char **tab, int cfd);
void		do_pwd(char **tab, int cfd);
void		send_file(char **tab, int cfd);
void		forked_process(int cfd);

#endif
