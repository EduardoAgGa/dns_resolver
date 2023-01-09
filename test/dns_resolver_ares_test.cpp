#include "doctest.h"

#include <array>
#include <cstring>
#include <string>

#include "dns_resolver.h"

static const char* const LOCALHOST_NAME = "localhost";
static const char* const EXPECTED_LOCALHOST_ADDR = "127.0.0.1";
static const char* const VALID_NAMESERVER = "8.8.8.8";
static const char* const VALID_SECONDARY_NAMESERVER = "8.8.4.4";
static const char* const VALID_HOSTNAME = "google.com";

static constexpr size_t BUFFER_SIZE = 16;

static void print_address(const char* address) {
  std::array<char, BUFFER_SIZE> buffer{};
  strcpy(buffer.data(), address);
  MESSAGE("The address is: ", std::string{buffer.data()});
}

TEST_CASE("Querying the nameserver for a valid hostname succeeds") {
  dns_resolver_create();

  char* address = nullptr;
  char* secondary_address = nullptr;
  dns_resolve_hostname(VALID_HOSTNAME, VALID_NAMESERVER, &address);
  dns_resolve_hostname(VALID_HOSTNAME, VALID_SECONDARY_NAMESERVER, &secondary_address);

  REQUIRE_NE(0, strcmp(EXPECTED_LOCALHOST_ADDR, address));
  REQUIRE_NE(0, strcmp(EXPECTED_LOCALHOST_ADDR, secondary_address));

  print_address(address);
  print_address(secondary_address);

  dns_resolver_destroy();
}
