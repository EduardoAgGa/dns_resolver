# DNS Resolver Library

This library provides an abstraction over the c-ares library for DNS resolution.

## Basic usage
The library must be initialize for use, and destroyed before program termination. After the initialization, FQDNs can be resolved; otherwise, the program will terminate.

> Library initialization
> 
> `dns_resolver_create();`

> Library closing
> 
> `dns_resolver_destroy();`

> Hostname resolution
>
> `dns_resolve_hostname(const char* hostname, const char* nameserver, char** address);`

> Example:
> ```
> dns_resolver_create();
> char* address;
> dns_resolve_hostname("google.com", "8.8.8.8", &address);
> dns_resolver_destroy();
> ```
>
> If hostname or nameserver are not initilized, you will face undefined behaviour or sigsegv faults &#8212; at a minimum, the pointer must point to NULL. On null or empty hostname or nameserver the library will return the localhost address.
> 

## Current state
The library is implemented using the C language, and can be used in both C and C++ applications. It allows FQDN resolution specifying the nameservers to query.

It only allows IPv4 protocol and A register resolution for now. Query timeouts and tries are also hardcoded right now.

## Future work
- Install targets
- Provide a C++ wrapper
- Support IPv6
