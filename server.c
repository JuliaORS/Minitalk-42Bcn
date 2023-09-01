/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:33:57 by julolle-          #+#    #+#             */
/*   Updated: 2023/06/28 17:34:45 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"

static void	sig_usr(int sig)
{
	static int	i = 7;
	static int	octet = 0;

	if (sig == SIGUSR1)
		octet = octet | (1 << i);
	i--;
	if (i < 0)
	{
		write (1, &octet, 1);
		i = 7;
		octet = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("%d\n", pid);
	signal(SIGUSR1, sig_usr);
	signal(SIGUSR2, sig_usr);
	while (1)
		pause ();
	return (0);
}
