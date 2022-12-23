#include "doctest.h"

#include <cstdlib>
#include <cstring>

extern "C" {
#include "fake_resolver_impl.h"
}

static const char* valid_nameserver = "8.8.8.8";
static const char* valid_hostname = "hostname.com";
static const char* expected_valid_address = "1.2.3.4";

#define MAX_STR_SIZE 32

static void allocate_address(char** address) {
  *address = (char*)malloc(sizeof(char) * (MAX_STR_SIZE + 1));
  strcpy(*address, "");
}

TEST_CASE("Querying the nameserver for a valid hostname success") {
  resolver_service_create();
  fake_resolver_expect_address(expected_valid_address);

  char* address;
  allocate_address(&address);  // Required, because the pimpl expect it
  resolver_service_resolve(valid_hostname, valid_nameserver, address);

  REQUIRE_EQ(0, strcmp(expected_valid_address, address));

  resolver_service_destroy();
}
