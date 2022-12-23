#ifndef network_dns_resolver_h
#define network_dns_resolver_h

#ifdef __cplusplus
extern "C" {
#endif

void dns_resolver_create(void);
void dns_resolver_destroy(void);

void dns_resolve_hostname(const char* hostname, const char* nameserver, char** address);

#ifdef __cplusplus
}
#endif

#endif /* network_dns_resolver_h */