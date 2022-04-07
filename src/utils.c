/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaramuk <mkaramuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:09:25 by mkaramuk          #+#    #+#             */
/*   Updated: 2022/02/08 18:47:16 by mkaramuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_usage_client(void)
{
	ft_printf("\e[1;33mHello folks!\e[0m This is the client side " \
		"program of the minitalk project.\n" \
		"I'll show you how to use this program\n\n" \
		"\e[0;32mclient (ARG) [SERVER_PID] [MESSAGE]\n\n" \
		"\t\e[4;37mARG\e[0m:\t\tYou can type --help for show this message\n" \
		"\t\e[4;37mSERVER_PID\e[0m:\tThe process" \
		"ID that signals will be sent\n" \
		"\t\e[4;37mMESSAGE\e[0m:\tThe message that you'll send\e[0m\n\n" \
		"This program licensed under GPL v3\n" \
		"If you have a problem or question you can\n" \
		"send a post to <a_developer_2002@outlook.com>\n\n");
}

void	send_signal(int signo, pid_t target_p)
{
	if (kill(target_p, signo) == -1)
		error("Signal couldn't sent");
}

void	error(char *msg)
{
	ft_printf("\e[0;31mError: %s\e[0m\n", msg);
	exit(1);
}

void	set_signal(int signo, struct sigaction *action)
{
	if (sigaction(signo, action, NULL) == -1)
		error("Signal couldn't set");
}
