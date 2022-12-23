#include "resolver_impl.h"

#include <ares.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ares_channel channel;

static void state_cb(void* data, int fd, int read, int write) {
  printf("Change state fd %d read:%d write:%d\n", fd, read, write);
}

result_t resolver_service_create(void) {
  struct ares_options options;
  int optmask = 0;

  int status = ares_library_init(ARES_LIB_INIT_ALL);
  if (status != ARES_SUCCESS) {
    printf("ares_library_init: %s\n", ares_strerror(status));
    return ERROR;
  }

  options.timeout
      = 1000;  // ! Time to respond to a query on the first try, then it scales linearly.
  options.tries = 2;
  // options.sock_state_cb = state_cb;
  optmask |= ARES_OPT_TIMEOUTMS;
  optmask |= ARES_OPT_TRIES;
  // optmask |= ARES_OPT_SOCK_STATE_CB;

  status = ares_init_options(&channel, &options, optmask);
  if (status != ARES_SUCCESS) {
    printf("ares_init_options: %s\n", ares_strerror(status));
    return ERROR;
  }

  return SUCCESS;
}

void resolver_service_destroy(void) {
  ares_destroy(channel);
  ares_library_cleanup();
}

void dns_callback_addrinfo(void* arg, int status, int timeouts, struct ares_addrinfo* result) {
  if (status != ARES_SUCCESS) {
    printf("Failed to lookup %s\n", ares_strerror(status));
    return;
  }

  char* address = (char*)arg;
  char ip[INET_ADDRSTRLEN];
  int i;
  struct ares_addrinfo_node* nodes = result->nodes;
  for (i = 0; nodes != NULL; ++i, nodes = nodes->ai_next) {
    inet_ntop(nodes->ai_family, nodes->ai_addr->sa_data, ip, sizeof(ip));
    if (nodes->ai_family == AF_INET) {
      inet_ntop(nodes->ai_family, (&((struct sockaddr_in*)nodes->ai_addr)->sin_addr), ip,
                sizeof(ip));
    }
    strcpy(address, ip);
  }
}

void wait_for_result(ares_channel channel) {
  for (;;) {
    struct timeval *tvp, tv;
    fd_set read_fds, write_fds;
    int nfds;

    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    nfds = ares_fds(channel, &read_fds, &write_fds);
    if (nfds == 0) {
      break;
    }
    tvp = ares_timeout(channel, NULL, &tv);
    select(nfds, &read_fds, &write_fds, NULL, tvp);
    ares_process(channel, &read_fds, &write_fds);
  }
}

static void set_hints(struct ares_addrinfo_hints* hints) {
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_DGRAM;
  hints->ai_flags |= AI_CANONNAME;
  hints->ai_flags |= AI_V4MAPPED;
}

void resolver_service_resolve(const char* hostname, const char* nameserver, char* address) {
  struct ares_addrinfo_hints hints;
  set_hints(&hints);
  ares_getaddrinfo(channel, hostname, nameserver, &hints, dns_callback_addrinfo, address);
  wait_for_result(channel);
}
