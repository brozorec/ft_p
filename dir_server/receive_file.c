/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:12:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 16:19:40 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			fill_content_file(char *buff_file, int fd_file, int *i)
{
	buff_file[1] = '\0';
	++(*i);
	if (write(fd_file, buff_file, 1) == -1)
		ft_putstr_fd("write() failed.\n", 2);
}

void			get_content_file(int cfd, char *name, int size)
{
	char			buff_file[2];
	int				fd_file;
	int				i;

	i = 0;
	if ((fd_file = open(name, O_TRUNC | O_CREAT | O_RDWR, ACCESSPERMS)) == -1)
		ft_putstr_fd("open() get_content_file failed.\n", 2);
	while (i < size)
	{
		if (recv(cfd, buff_file, 1, 0) > 0)
			fill_content_file(buff_file, fd_file, &i);
		else
		{
			fatal("Connection closed unexpectedly.\n");
			close(fd_file);
			return ;
		}
	}
	close(fd_file);
}

void			receive_file(char *file, int cfd)
{
	char			*buff;
	char			*name;
	int				size;

	buff = receive_msg(cfd);
	if (ft_strncmp(buff, "OK", 2) == 0)
	{
		ft_strdel(&buff);
		buff = receive_msg(cfd);
		size = ft_atoi(buff);
		ft_strdel(&buff);
		if ((name = ft_strrchr(file, '/')) != 0)
			get_content_file(cfd, name + 1, size);
		else
			get_content_file(cfd, file, size);
	}
	else
	{
		ft_putendl(buff);
		ft_strdel(&buff);
	}
}
