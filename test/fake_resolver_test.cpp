#include "doctest.h"

#include <cstdlib>
#include <cstring>

extern "C" {
#include "fake_resolver_impl.h"
}

static const char* const VALID_NAMESERVER = "8.8.8.8";
static const char* const VALID_HOSTNAME = "hostname.com";
static const char* const EXPECTED_VALID_ADDRESS = "1.2.3.4";

static constexpr size_t MAX_STR_SIZE = 32;

static void allocate_address(char** address) {
  *address = (char*)malloc(sizeof(char) * (MAX_STR_SIZE + 1));
  strcpy(*address, "");
}

TEST_CASE("Querying the nameserver for a valid hostname success") {
  resolver_service_create();
  fake_resolver_expect_address(EXPECTED_VALID_ADDRESS);

  char* address = nullptr;
  allocate_address(&address);  // Required, because the pimpl expect it
  resolver_service_resolve(VALID_HOSTNAME, VALID_NAMESERVER, address);

  REQUIRE_EQ(0, strcmp(EXPECTED_VALID_ADDRESS, address));

  resolver_service_destroy();
}
