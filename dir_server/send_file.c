/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 17:18:19 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/15 18:39:20 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char		*get_file_size(int fd_file)
{
	struct stat		buf;
	char			*size;

	size = 0;
	if (fstat(fd_file, &buf) != -1)
	{
		size = ft_itoa(buf.st_size);
	}
	size = ft_realloc(size, 3);
	size = ft_strcat(size, "\r\n");
	return (size);
}

void		read_and_send(int cfd, int fd_file, int size)
{
	int				ret;
	char			buff[2];
	int				i;

	i = 0;
	while (i < size)
	{
		if ((ret = read(fd_file, buff, 1)) > 0)
		{
			buff[1] = '\0';
			i += ret;
			if (send(cfd, buff, 1, 0) == -1)
				err_msg("send() open_and_send failed.\n");
		}
	}
	if (send(cfd, "SUCCESS\nFile sent.\r\n", 20, MSG_DONTWAIT) == -1)
				err_msg("send() open_and_send failed.\n");
	close(fd_file);
}

void		open_file(char *file, int cfd)
{
	int			fd_file;
	char		*size;
	int			sz;

	if ((fd_file = open(file, O_RDWR)) == -1)
	{
		if (send(cfd, "ERROR\nNo such file.\r\n", 21, MSG_DONTWAIT) == -1)
			err_msg("send() open_file failed.\n");
		return ;
	}
	else
	{
		if (send(cfd, "OK\r\n", 4, MSG_DONTWAIT) == -1)
			err_msg("send() open_file failed.\n");
		size = get_file_size(fd_file);
		if (send(cfd, size, ft_strlen(size), MSG_DONTWAIT) == -1)
			err_msg("send() open_file failed.\n");
		size[ft_strlen(size) - 2] = '\0';
		sz = ft_atoi(size);
		printf("%d\n", sz);
		read_and_send(cfd, fd_file, sz);
	}
}

void		send_file(char **tab, int cfd)
{
	if (tab[1] == 0 || tab[2] != 0)
	{
		if (send(cfd, "ERROR\nUsage get: get <file>\r\n", 29, MSG_DONTWAIT) == -1)
			err_msg("send() send failed.\n");
		return ;
	}
	open_file(tab[1], cfd);
}
