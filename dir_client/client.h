/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:40:32 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/12 13:23:14 by bbarakov         ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/mman.h>
# include "../libft/includes/libft.h"
# include "get_next_line.h"

void		err_msg(char *err);
void		usage(char *str);
void		do_interaction(int cfd);
char		*receive_msg(int cfd);
void		receive_file(int cfd, char *name);

// void dump_client(char *data_buffer, int length)
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
// 				// if((byte > 31) && (byte < 127)) // Outside printable char range
// 				// 	printf("%c", byte);
// 				// else
// 				// 	printf(".");
// 				// printf("%d\n", int (byte));
// 			}
// 			printf("\n"); // End of the dump line (each line is 16 bytes)
// 		}
// 	}
// }

#endif
