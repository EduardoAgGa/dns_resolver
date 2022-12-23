#include "dns_resolver.h"
#include "resolver_impl.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 32

void dns_resolver_create(void) {
  resolver_service_create();
}

void dns_resolver_destroy(void) {
  resolver_service_destroy();
}

static void allocate_address(char** address) {
  *address = (char*)malloc(sizeof(char) * (MAX_STR_SIZE + 1));
  strcpy(*address, "");
}

static bool is_valid(const char* name) {
  return (name != NULL);
}

static bool is_localhost(const char* name) {
  return strcmp("localhost", name) == 0 || strcmp("", name) == 0;
}

static void do_resolve(const char* hostname, const char* nameserver, char* address) {
  resolver_service_resolve(hostname, nameserver, address);
}

void dns_resolve_hostname(const char* hostname, const char* nameserver, char** address) {
  allocate_address(address);

  if (!is_valid(hostname) || !is_valid(nameserver)) {
    strcpy(*address, "");
    return;
  }

  if (!is_localhost(hostname)) {
    do_resolve(hostname, nameserver, *address);
    return;
  }

  strcpy(*address, "127.0.0.1");
}
