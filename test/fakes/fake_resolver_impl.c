#include "fake_resolver_impl.h"
#include "resolver_common.h"

#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 32

char* expected_address;

result_t fake_resolver_create(void) {
  expected_address = (char*)malloc(sizeof(char) * (MAX_STR_SIZE + 1));
  strcpy(expected_address, "");

  return SUCCESS;
}

void fake_resolver_destroy(void) {}

void fake_resolver_expect_address(const char* address) {
  strcpy(expected_address, address);
}

result_t resolver_service_create(void) {
  return fake_resolver_create();
}

void resolver_service_destroy(void) {
  fake_resolver_destroy();
}

void resolver_service_resolve(const char* hostname, const char* nameserver, char* address) {
  strcpy(address, expected_address);
}
