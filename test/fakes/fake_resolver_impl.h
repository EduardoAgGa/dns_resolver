#include "resolver_common.h"
#include "resolver_impl.h"

result_t fake_resolver_create(void);
void fake_resolver_destroy(void);

void fake_resolver_expect_address(const char* address);
// void fake_resolver_service_resolve(const char* hostname, const char* nameserver, char* address);
