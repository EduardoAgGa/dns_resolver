#ifndef network_dns_resolver_impl_h
#define network_dns_resolver_impl_h

#include "resolver_common.h"

result_t resolver_service_create(void);
void resolver_service_destroy(void);

void resolver_service_resolve(const char* hostname, const char* nameserver, char* address);

#endif /* network_dns_resolver_impl_h */