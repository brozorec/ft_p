/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:42 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/13 14:17:03 by bbarakov         ###   ########.fr       */
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
# include "get_next_line.h"

void		err_msg(char *err);
void		usage(char *str);
int 		get_next_line(int fd, char **line);
void		do_ls(char **tab, int cfd);
void		do_cd(char **tab, int cfd, char *starting_dir);
char		*take_env_var(void);
void		do_pwd(char **tab, int cfd);
char		*take_cwd(void);
void		send_file(char **tab, int cfd);
void		forked_process(int cfd);

// void dump(char *data_buffer, int length)
// {
// 	char byte;
// 	int i, j;

// 	for(i=0; i < length; i++)
// 	{
// 		byte = data_buffer[i];
// 		printf("%02x ", data_buffer[i]); // Display byte in hex.
// 		if(((i%16)==15) || (i==length-1))
// 		{
// 			for(j=0; j < 15-(i%16); j++)
// 				printf(" ");
// 			printf("| ");
// 			for(j=(i-(i%16)); j <= i; j++)
// 			{
// 				byte = data_buffer[j];
// 				if((byte > 31) && (byte < 127)) // Outside printable char range
// 					printf("%c", byte);
// 				else
// 					printf(".");
// 			}
// 			printf("\n"); // End of the dump line (each line is 16 bytes)
// 		}
// 	}
// }

#endif
