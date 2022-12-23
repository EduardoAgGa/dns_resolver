#include "doctest.h"

#include <cstring>

#include "dns_resolver.h"

extern "C" {
#include "fake_resolver_impl.h"
}

static const char* localhost_name = "localhost";
static const char* expected_localhost_addr = "127.0.0.1";
static const char* valid_nameserver = "8.8.8.8";
static const char* valid_hostname = "hostname.com";
static const char* expected_valid_address = "1.2.3.4";
static const char* expected_max_length_address = "123.123.123.123";
static const char* expected_empty_address = "";

class DnsResolver {
  public:
  DnsResolver() {
    dns_resolver_create();
  }
  ~DnsResolver() {
    dns_resolver_destroy();
  }
};

TEST_CASE_FIXTURE(DnsResolver, "Localhost always resolves to 127.0.0.1") {
  char* address;
  dns_resolve_hostname(localhost_name, valid_nameserver, &address);

  REQUIRE_EQ(0, strcmp(expected_localhost_addr, address));
}

TEST_CASE_FIXTURE(DnsResolver, "An empty hostname is equivalent to localhost") {
  const char* hostname = "";

  char* address;
  dns_resolve_hostname(hostname, valid_nameserver, &address);

  REQUIRE_EQ(0, strcmp(expected_localhost_addr, address));
}

TEST_CASE_FIXTURE(DnsResolver, "An empty nameserver is is equivalent to localhost") {
  const char* nameserver = "";

  char* address;
  dns_resolve_hostname(localhost_name, nameserver, &address);

  REQUIRE_EQ(0, strcmp(expected_localhost_addr, address));
}

TEST_CASE_FIXTURE(DnsResolver, "Querying the nameserver for a valid hostname succeeds") {
  fake_resolver_expect_address(expected_valid_address);

  char* address;
  dns_resolve_hostname(valid_hostname, valid_nameserver, &address);

  REQUIRE_EQ(0, strcmp(expected_valid_address, address));
}

TEST_CASE_FIXTURE(DnsResolver, "Reusing address for another query is allowed") {
  fake_resolver_expect_address(expected_valid_address);

  char* address;
  dns_resolve_hostname(localhost_name, valid_nameserver, &address);
  dns_resolve_hostname(valid_hostname, valid_nameserver, &address);

  REQUIRE_EQ(0, strcmp(expected_valid_address, address));
}

TEST_CASE_FIXTURE(DnsResolver, "On query timeout, the address is empty") {
  fake_resolver_expect_address(expected_empty_address);

  char* address;
  dns_resolve_hostname(valid_hostname, valid_nameserver, &address);

  REQUIRE_EQ(0, strcmp(expected_empty_address, address));
}

TEST_CASE_FIXTURE(DnsResolver, "An IPv4 address has a maximum of 15 characters") {
  fake_resolver_expect_address(expected_max_length_address);

  char* address;
  dns_resolve_hostname(valid_hostname, valid_nameserver, &address);

  REQUIRE_LT(strlen(address), 16);
}
