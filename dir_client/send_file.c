/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 17:18:19 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 17:04:06 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
			{
				close(fd_file);
				return ;
			}
		}
	}
	ft_putstr("SUCCESS\nFile sent.\n");
	close(fd_file);
}

void		open_file(char *file, char *buff_input, int cfd)
{
	int			fd_file;
	char		*size;
	int			sz;

	if ((fd_file = open(file, O_RDWR)) == -1)
	{
		ft_putstr_fd("ERROR\nNo such file.\n", 2);
		return ;
	}
	else
	{
		if (send_msg(buff_input, cfd) == 0)
			return ;
		send_msg("OK", cfd);
		size = get_file_size(fd_file);
		send_msg(size, cfd);
		sz = ft_atoi(size);
		ft_strdel(&size);
		read_and_send(cfd, fd_file, sz);
	}
}

void		send_file(int cfd, char *buff_input)
{
	char		**tab;
	int			i;

	tab = ft_strsplit(buff_input, ' ');
	if (tab[1] == 0 || tab[2] != 0)
		ft_putstr_fd("ERROR\nUsage put: put <file>\n", 2);
	else
		open_file(tab[1], buff_input, cfd);
	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		++i;
	}
}
