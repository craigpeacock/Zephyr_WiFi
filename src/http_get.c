/* 
 * Copyright (c) 2023 Craig Peacock.
 * 
 * API Information:
 * https://docs.zephyrproject.org/3.2.0/connectivity/networking/api/http.html
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <zephyr/net/socket.h>
#include <zephyr/kernel.h>
#include <zephyr/net/http/client.h>

void nslookup(const char * hostname, struct zsock_addrinfo **results)
{
	int err;
	
	struct zsock_addrinfo hints = {
		//.ai_family = AF_INET,     // Allow IPv4 Address
		.ai_family = AF_UNSPEC,		// Allow IPv4 or IPv6	
		.ai_socktype = SOCK_STREAM,
	};

	err = zsock_getaddrinfo(hostname, NULL, &hints, (struct zsock_addrinfo **) results);
	if (err) {
		printf("getaddrinfo() failed, err %d\n", errno);
		return;
	}
}

void print_addrinfo_results(struct zsock_addrinfo **results)
{
	char ipv4[INET_ADDRSTRLEN];
	char ipv6[INET6_ADDRSTRLEN];
	struct sockaddr_in *sa;
	struct sockaddr_in6 *sa6;
	struct zsock_addrinfo *rp;
	
	for (rp = (struct zsock_addrinfo *)results; rp != NULL; rp = rp->ai_next) {
		if (rp->ai_addr->sa_family == AF_INET) {
			// IPv4 Address
			sa = (struct sockaddr_in *) rp->ai_addr;
			zsock_inet_ntop(AF_INET, &sa->sin_addr, ipv4, INET_ADDRSTRLEN);
			printf("IPv4: %s\n", ipv4);
		}
		if (rp->ai_addr->sa_family == AF_INET6) {
			// IPv6 Address
			sa6 = (struct sockaddr_in6 *) rp->ai_addr;
			zsock_inet_ntop(AF_INET6, &sa6->sin6_addr, ipv6, INET6_ADDRSTRLEN);
			printf("IPv6: %s\n", ipv6);
		}
	}
}

int connect_socket(struct zsock_addrinfo **results)
{
	int sock;
	struct zsock_addrinfo *rp;
	struct sockaddr_in *sa;

	// Create Socket
	sock = zsock_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		printk("Error creating socket\n");
		return(-1);
	}
	
	// Iterate through until we get a successful connection
	for (rp = (struct zsock_addrinfo *)results; rp != NULL; rp = rp->ai_next) {
		if (rp->ai_addr->sa_family == AF_INET) {
			// IPv4 Address
			sa = (struct sockaddr_in *) rp->ai_addr;
			sa->sin_port = htons(80);
			zsock_connect(sock, (struct sockaddr *) sa, sizeof(struct sockaddr_in));
			if (sock > 0)
				break;
		}
	}
	
	return(sock);
}

static void http_response_cb(struct http_response *rsp,
			enum http_final_call final_data,
			void *user_data)
{
	if (final_data == HTTP_DATA_MORE) {
		printk("Partial data received (%zd bytes)\n", rsp->data_len);
	} else if (final_data == HTTP_DATA_FINAL) {
		printk("All the data received (%zd bytes)\n", rsp->data_len);
	}

	printk("Bytes Recv %zd\n", rsp->data_len);
	printk("Response status %s\n", rsp->http_status);
	printk("Recv Buffer Length %zd\n", rsp->recv_buf_len);
	printk("%s\n",rsp->recv_buf);
}

void http_get(int sock, char * hostname, char * url)
{
	struct http_request req = { 0 };
	static uint8_t recv_buf[512];
	int ret;

	req.method = HTTP_GET;
	req.url = url;
	req.host = hostname;
	req.protocol = "HTTP/1.1";
	req.response = http_response_cb;
	req.recv_buf = recv_buf;
	req.recv_buf_len = sizeof(recv_buf);

	/* sock is a file descriptor referencing a socket that has been connected
	* to the HTTP server.
	*/
	ret = http_client_req(sock, &req, 5000, NULL);
}