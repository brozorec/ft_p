/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:39:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/18 15:39:31 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		sig_pipe(int sig)
{
	if (sig == 13)
	{
		err_msg("Connection closed by server.\n");
		return ;
	}
}

int			create_socket(char *host_name, char *port)
{
	int					cfd;
	int 				i;
	// struct addrinfo		hints;
	struct addrinfo		*r;

	// ft_memset(&hints, 0, sizeof(hints));
	// hints.ai_family = AF_INET6;
	// hints.ai_socktype = SOCK_STREAM;
	// hints.ai_protocol = IPPROTO_TCP;
	// hints.ai_flags = AI_ALL | AI_V4MAPPED;
	if (getaddrinfo(host_name, port, 0, &r) != 0)
		fatal("Connection failed.\n");
	while (r)
	{
		printf("%s\n", "tuk");
		printf("%i\n", r->ai_family);
		if ((cfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol)) < 0)
		{
			ft_putstr_fd("socket()\n", 2);
		}
		if ((i = connect(cfd, r->ai_addr, r->ai_addrlen)) < 0)
		{
			ft_putstr_fd("connect()\n", 2);
			close(cfd);
			cfd = 0;
		}
		if (i == 0)
			break ;
		r = r->ai_next;
	}
	return (cfd);
}

int			main(int ac, char **av)
{
	int					cfd;

	signal(SIGPIPE, sig_pipe);
	if (ac != 3)
		fatal("Usage: client <addr> <port>\n");
	cfd = 0;
	while (cfd == 0)
		cfd = create_socket(av[1], av[2]);
	do_interaction(cfd);
	// else
	// 	ft_putstr_fd("No connection.\n", 2);
	return (0);
}


	// if ((cfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
	// 	err_msg("socket() failed.\n");
	// if (connect(cfd, res->ai_addr, res->ai_addrlen) < 0)
	// 	fatal("Connection failed.\n");
