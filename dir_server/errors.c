/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:46:22 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/09 12:20:23 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		err_msg(char *err)
{
	printf("%s", err);
	exit(-1);
}

void		usage(char *str)
{
	printf("Usage %s <port>\n", str);
	exit(-1);
}
