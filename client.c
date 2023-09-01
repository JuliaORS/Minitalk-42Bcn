/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:34:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/07/11 11:47:44 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf.h"

int	handler_str(pid_t pid, char *str)
{
	int	i;
	int	dig;

	i = 0;
	while (str[i])
	{
		dig = 7;
		while (dig >= 0)
		{
			if (str[i] & (1 << dig))
			{
				if (kill (pid, SIGUSR1) == -1)
					return (-1);
			}
			else
			{
				if (kill (pid, SIGUSR2) == -1)
					return (-1);
			}
			dig--;
			usleep (500);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	result = result * sign;
	return (result);
}

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' > str[i] && str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (argc != 3 || ft_strisdigit(argv[1]) == -1)
	{
		ft_printf("Invalid arguments.\nTry: ./client <PID> <MESSAGE>\n");
		return (0);
	}
	else
	{
		pid = ft_atoi(argv[1]);
		if (handler_str(pid, argv[2]) == -1)
		{
			ft_printf("Invalid PID");
			return (0);
		}
	}
}
