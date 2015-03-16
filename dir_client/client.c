/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:39:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 18:16:42 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		sig_pipe(int sig)
{
	if (sig == 13)
	{
		err_msg("Connection was closed by server.\n");
		return ;
	}
}

int			create_socket(char *addr, int port)
{
	int					cfd;
	struct protoent		*proto;
	struct sockaddr_in	clnt_addr;

	if ((proto = getprotobyname("tcp")) == 0)
		err_msg("getprotobyname() failed.\n");
	if ((cfd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		err_msg("socket() failed.\n");
	clnt_addr.sin_family = AF_INET;
	clnt_addr.sin_port = htons(port);
	clnt_addr.sin_addr.s_addr = inet_addr(addr);
	ft_memset(&(clnt_addr.sin_zero), '\0', 8);
	if (connect(cfd, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr)) == -1)
		fatal("Connection failed.\n");
	return (cfd);
}

int			main(int ac, char **av)
{
	int					cfd;
	int					port;

	signal(SIGPIPE, sig_pipe);
	if (ac != 3)
		fatal("Usage: client <addr> <port>\n");	// av[1] = hostaddr
	if ((port = ft_atoi(av[2])) == 0)
		fatal("Enter valid port.\n");
	cfd = create_socket(av[1], port);
	do_interaction(cfd);
	return (0);
}
