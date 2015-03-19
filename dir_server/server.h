/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:42 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/17 17:29:46 by bbarakov         ###   ########.fr       */
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
# include <sys/stat.h>
# include "../libft/includes/libft.h"

void		fatal(char *err);
void		usage(char *str);
void		do_ls(char **tab, int cfd);
void		do_cd(char **tab, int cfd, char *dir_base);
char		*take_env_var(void);
void		do_pwd(char **tab, int cfd);
char		*take_cwd(int flag_print);
char		*receive_msg(int cfd);
int			send_msg(char *buff, int cfd);
void		send_file(char **tab, int cfd);
void		receive_file(char *file, int cfd);
void		accept_connections(int sfd);
void		forked_process(int cfd);

#endif
