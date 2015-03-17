/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:03 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/17 17:29:34 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		sig_child(int sig)
{
	int				status;

	if (sig == 20)
	{
		wait4(0, &status, WUNTRACED, 0);
		return ;
	}
}

void		sig_pipe(int sig)
{
	if (sig == 13)
	{
		fatal("Connection closed by client.\n");
		return ;
	}
}

int			create_socket(char *port)
{
	int					sfd;
	int					yes;
	struct addrinfo		hints;
	struct addrinfo		*res;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(0, port, &hints, &res) != 0)
		fatal("Connection failed.\n");
	if ((sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
		fatal("socket() failed.\n");
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		fatal("setsockopt() failed.\n");
	if (bind(sfd, res->ai_addr, res->ai_addrlen) < 0)
		fatal("Connection failed. Probably port is not valid.\n");
	if (listen(sfd, 10) == -1)
		fatal("listen() failed.\n");
	return (sfd);
}

void		accept_connections(int sfd)
{
	int					cfd;
	struct sockaddr_in	clnt_addr;
	socklen_t			add_size;
	pid_t				child;

	add_size = sizeof(clnt_addr);
	while (1)
	{
		if ((cfd = accept(sfd, (struct sockaddr *)&clnt_addr, &add_size)) == -1)
			fatal("accept() failed.\n");
		if ((child = fork()) == 0)
		{
			close(sfd);
			forked_process(cfd);
		}
		ft_putendl("New client");
		close(cfd);
	}
}

int			main(int ac, char **av)
{
	int				sfd;

	if (ac != 2)
		fatal("Usage: serveur <port>\n");
	signal(SIGCHLD, sig_child);
	signal(SIGPIPE, sig_pipe);
	sfd = create_socket(av[1]);
	accept_connections(sfd);
	close(sfd);
	return (0);
}
