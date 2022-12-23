#include "doctest.h"

#include <cstring>

#include "dns_resolver.h"

static const char* localhost_name = "localhost";
static const char* expected_localhost_addr = "127.0.0.1";
static const char* valid_nameserver = "8.8.8.8";
static const char* valid_secondary_nameserver = "8.8.4.4";
static const char* valid_hostname = "google.com";

static void print_address(const char* address) {
  char buffer[16];
  strcpy(buffer, address);
  MESSAGE("The address is: ", buffer);
}

TEST_CASE("Querying the nameserver for a valid hostname succeeds") {
  dns_resolver_create();

  char* address;
  char* secondary_address;
  dns_resolve_hostname(valid_hostname, valid_nameserver, &address);
  dns_resolve_hostname(valid_hostname, valid_secondary_nameserver, &secondary_address);

  REQUIRE_NE(0, strcmp(expected_localhost_addr, address));
  REQUIRE_NE(0, strcmp(expected_localhost_addr, secondary_address));

  print_address(address);
  print_address(secondary_address);

  dns_resolver_destroy();
}
