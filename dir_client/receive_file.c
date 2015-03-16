/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:12:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 18:42:20 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			fill_content_file(char *buff_file, int fd_file, int *i)
{
	buff_file[1] = '\0';
	++(*i);
	if (write(fd_file, buff_file, 1) == -1)
		err_msg("write() failed.\n");
}

void			get_content_file(int cfd, char *name, int size)
{
	char			*buff;
	char			buff_file[2];
	int				fd_file;
	int				i;

	i = 0;
	if ((fd_file = open(name, O_TRUNC | O_CREAT | O_RDWR, ACCESSPERMS)) == -1)
		err_msg("open() failed.\n");
	while (i < size)
	{
		if (recv(cfd, buff_file, 1, 0) > 0)
			fill_content_file(buff_file, fd_file, &i);
		else
		{
			err_msg("Connection closed unexpectedly.\n");
			close(fd_file);
			return ;
		}
	}
	close(fd_file);
	buff = receive_msg(cfd);
	ft_putendl(buff);
	ft_strdel(&buff);
}

void			receive_file(int cfd, char *file)
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
