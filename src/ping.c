/* 
 * Copyright (c) 2024 Craig Peacock.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <zephyr/net/socket.h>
#include <zephyr/kernel.h>
#include <zephyr/net/icmp.h>
#include <zephyr/net/net_ip.h>

static int icmp_echo_reply_handler(struct net_icmp_ctx *ctx,
				struct net_pkt *pkt,
				struct net_icmp_ip_hdr *hdr,
				struct net_icmp_hdr *icmp_hdr,
				void *user_data)
{
	uint32_t cycles;
	char ipv4[INET_ADDRSTRLEN];
	zsock_inet_ntop(AF_INET, &hdr->ipv4->src, ipv4, INET_ADDRSTRLEN);

	uint32_t *start_cycles = user_data;

	cycles = k_cycle_get_32() - *start_cycles;

	printk("Reply from %s: bytes=%d time=%dms TTL=%d\r\n",
			ipv4,
			ntohs(hdr->ipv4->len),
			((uint32_t)k_cyc_to_ns_floor64(cycles) / 1000000),
			hdr->ipv4->ttl);

	return 0;
}

void ping(char* ipv4_addr, uint8_t count)
{
	uint32_t cycles;
	int ret;
	struct net_icmp_ctx icmp_context;

	// Register handler for echo reply
	ret = net_icmp_init_ctx(&icmp_context, NET_ICMPV4_ECHO_REPLY, 0, icmp_echo_reply_handler);
	if (ret != 0) {
		printk("Failed to init ping, err: %d", ret);
	}

	struct net_if *iface = net_if_get_default();
	struct sockaddr_in dst_addr;
	net_addr_pton(AF_INET, ipv4_addr, &dst_addr.sin_addr);
	dst_addr.sin_family = AF_INET;

	for (int i = 0; i < count; i++)
	{
		cycles = k_cycle_get_32();
		ret = net_icmp_send_echo_request(&icmp_context, iface, (struct sockaddr *)&dst_addr, NULL, &cycles);
		if (ret != 0) {
			printk("Failed to send ping, err: %d", ret);
		}
		k_sleep(K_SECONDS(2));
	}

	net_icmp_cleanup_ctx(&icmp_context);
}
