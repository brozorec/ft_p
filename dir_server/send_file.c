/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 17:18:19 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 16:00:13 by bbarakov         ###   ########.fr       */
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
	return (size);
}

void		read_and_send(int cfd, int fd_file, int size)
{
	char			buff[2];
	int				i;

	i = 0;
	while (i < size)
	{
		if (read(fd_file, buff, 1) > 0)
		{
			buff[1] = '\0';
			++i;
			if (send(cfd, buff, 1, 0) == -1)
			{
				close(fd_file);
				return ;
			}
		}
	}
	send_msg("SUCCESS\nFile received.", cfd);
	close(fd_file);
}

void		open_file(char *file, int cfd)
{
	int			fd_file;
	char		*size;
	int			sz;

	if ((fd_file = open(file, O_RDWR)) == -1)
	{
		send_msg("ERROR\nNo such file.", cfd);
		return ;
	}
	else
	{
		send_msg("OK", cfd);
		size = get_file_size(fd_file);
		send_msg(size, cfd);
		sz = ft_atoi(size);
		ft_strdel(&size);
		read_and_send(cfd, fd_file, sz);
	}
}

void		send_file(char **tab, int cfd)
{
	if (tab[1] == 0 || tab[2] != 0)
	{
		send_msg("ERROR\nUsage get: get <file>", cfd);
		return ;
	}
	open_file(tab[1], cfd);
}
