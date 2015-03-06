/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:03 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/06 19:50:58 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void		sig_child(int sig)
{
	pid_t				child;
	int 				status;

	if (sig == 20)
	{
		child = wait4(0, &status, WUNTRACED, 0);
		return ;
	}
}

int			create_socket(int port)
{
	int					sfd;
	struct protoent		*proto;
	struct sockaddr_in	host_addr;

	if ((proto = getprotobyname("tcp")) == 0)
		err_msg("getprotobyname() failed.\n");
	if ((sfd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		err_msg("socket() failed.\n");
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);
	host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ft_memset(&(host_addr.sin_zero), '\0', 8);
	if (bind(sfd, (const struct sockaddr *)&host_addr, sizeof(host_addr)) == -1)
		err_msg("bind() failed.\n");
	if (listen(sfd, 10) == -1)
		err_msg("listen() failed.\n");
	return (sfd);
}

void		forked_examine_buff(char *buff, int cfd)
{
	if (ft_strcmp(buff, "ls") == 0)
	{
		if (execl("/bin/ls", "ls", 0) == -1)
			err_msg("execl() failed.\n");
	}
	if (ft_strcmp(buff, "quit") == 0)
	{
		close(cfd);
		exit(0);
	}
}

void		forked_proceed(int cfd)
{
	char				*buff;
	int 				ret;

	while ((ret = get_next_line(cfd, &buff)) != -1)
	{
		buff[ret - 1] = '\0';
		forked_examine_buff(buff, cfd);
		free(buff);
		// printf("%s\n", buff);
	}
	err_msg("GNL failed.\n");
}

void		accept_connections(int sfd)
{
	int					cfd;
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size;
	pid_t				child;

	client_addr_size = sizeof(client_addr);
	while (1)
	{
		if ((cfd = accept(sfd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1)
			err_msg("accept() failed.\n");
		if ((child = fork()) == 0)
		{
			close(sfd);
			forked_proceed(cfd);
		}
		wait(0);
		printf("%s\n", "tuk");
		close(cfd);
	}
}

int			main(int ac, char **av)
{
	int				sfd;
	int				port;

	if (ac != 2)
		usage(av[0]);
	if ((port = ft_atoi(av[1])) == 0)
		usage(av[0]);
	signal(SIGCHLD, sig_child);
	sfd = create_socket(port);
	accept_connections(sfd);
	close(sfd);
	return (0);
}
