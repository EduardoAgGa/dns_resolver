#include "doctest.h"

#include <cstring>

#include "dns_resolver.h"

extern "C" {
#include "fake_resolver_impl.h"
}

static const char* const LOCALHOST_NAME = "localhost";
static const char* const EXPECTED_LOCALHOST_ADDR = "127.0.0.1";
static const char* const VALID_NAMESERVER = "8.8.8.8";
static const char* const VALID_HOSTNAME = "hostname.com";
static const char* const EXPECTED_VALID_ADDRESS = "1.2.3.4";
static const char* const EXPECTED_MAX_LENGTH_ADDRESS = "123.123.123.123";
static const char* const EXPECTED_EMPTY_ADDRESS = "";

class dns_resolver {
  public:
  dns_resolver() {
    dns_resolver_create();
  }
  ~dns_resolver() {
    dns_resolver_destroy();
  }
};

TEST_CASE_FIXTURE(dns_resolver, "Localhost always resolves to 127.0.0.1") {
  char* address = nullptr;
  dns_resolve_hostname(LOCALHOST_NAME, VALID_NAMESERVER, &address);

  REQUIRE_EQ(0, strcmp(EXPECTED_LOCALHOST_ADDR, address));
}

TEST_CASE_FIXTURE(dns_resolver, "An empty hostname is equivalent to localhost") {
  const char* hostname = "";

  char* address = nullptr;
  dns_resolve_hostname(hostname, VALID_NAMESERVER, &address);

  REQUIRE_EQ(0, strcmp(EXPECTED_LOCALHOST_ADDR, address));
}

TEST_CASE_FIXTURE(dns_resolver, "An empty nameserver is is equivalent to localhost") {
  const char* nameserver = "";

  char* address = nullptr;
  dns_resolve_hostname(LOCALHOST_NAME, nameserver, &address);

  REQUIRE_EQ(0, strcmp(EXPECTED_LOCALHOST_ADDR, address));
}

TEST_CASE_FIXTURE(dns_resolver, "Querying the nameserver for a valid hostname succeeds") {
  fake_resolver_expect_address(EXPECTED_VALID_ADDRESS);

  char* address = nullptr;
  dns_resolve_hostname(VALID_HOSTNAME, VALID_NAMESERVER, &address);

  REQUIRE_EQ(0, strcmp(EXPECTED_VALID_ADDRESS, address));
}

TEST_CASE_FIXTURE(dns_resolver, "Reusing address for another query is allowed") {
  fake_resolver_expect_address(EXPECTED_VALID_ADDRESS);

  char* address = nullptr;
  dns_resolve_hostname(LOCALHOST_NAME, VALID_NAMESERVER, &address);
  dns_resolve_hostname(VALID_HOSTNAME, VALID_NAMESERVER, &address);

  REQUIRE_EQ(0, strcmp(EXPECTED_VALID_ADDRESS, address));
}

TEST_CASE_FIXTURE(dns_resolver, "On query timeout, the address is empty") {
  fake_resolver_expect_address(EXPECTED_EMPTY_ADDRESS);

  char* address = nullptr;
  dns_resolve_hostname(VALID_HOSTNAME, VALID_NAMESERVER, &address);

  REQUIRE_EQ(0, strcmp(EXPECTED_EMPTY_ADDRESS, address));
}

TEST_CASE_FIXTURE(dns_resolver, "An IPv4 address has a maximum of 15 characters") {
  fake_resolver_expect_address(EXPECTED_MAX_LENGTH_ADDRESS);

  char* address = nullptr;
  dns_resolve_hostname(VALID_HOSTNAME, VALID_NAMESERVER, &address);

  REQUIRE_LT(strlen(address), 16);
}
