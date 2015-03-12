/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:12:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/12 17:33:08 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			get_content_file(int cfd, char *name_file, int size_file)
{
	char			*buff_recv;
	int				fd_file;
	int				ret;

	if ((fd_file = open(name_file, O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1)
		err_msg("open() get_content_file failed.\n");
	printf("%d\n", fd_file);
	if ((buff_recv = receive_msg(cfd)) != 0)
	{
		// buff_recv[ret] = '\0';
		if ((ret = write(fd_file, buff_recv, size_file)) == -1 )
		{
			// printf("%d\n", errno);
			err_msg("Not received the whole amount of bytes.\n");
		}
		close(fd_file);
		// printf("%d\n", ret);
	}
	printf("%s\n", receive_msg(cfd));
}

void			receive_file(int cfd, char *name_file)
{
	// int				ret;
	char			*buff_recv;
	int				size_file;

	buff_recv = receive_msg(cfd);
	printf("%s\n", buff_recv);
	if (ft_strncmp(buff_recv, "OK", 2) == 0)
	{
		// if ((ret = recv(cfd, buff_recv, 1023, 0)) == -1)
		// 	err_msg("recv() failed receive_file.\n");
		// buff_recv[ret] = '\0';
		buff_recv = receive_msg(cfd);
		printf("%s\n", buff_recv);
		size_file = ft_atoi(buff_recv);
		get_content_file(cfd, name_file, size_file);
	}
	else
		printf("%s\n", buff_recv);
}
