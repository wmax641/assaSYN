#ifndef IP_HELPER_HEADER
#define IP_HELPER_HEADER

#include <string.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/types.h>

#define IPv4_LEN 4
#define IPv6_LEN 16

/* get ip address of host, 
 * pass in an already allocated memory buffer that's at least long enough to store 
 * ip address (4 bytes for ipv4 and 16 bytes for ipv6)
 *
 * Function will look through currently active interfaces of the specified family
 * that are NOT loopback, and write the ip adress of the first match into the passed in
 * buffer. ip address is written in host ordering
 *
 * Returns 0 if found and no problems, otherwise -1
 * eg. 
 *    uint32_t ipaddr
 *    get_host_ipv4(&ipaddr);
 *    printf("%u\n", ipaddr);
 * >3232278787    ** equivalent to 192.168.169.3) **
 *
 * */
int get_host_ipv4(void *buf);
int get_host_ipv6(void *buf);


#endif
