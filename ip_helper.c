#include "ip_helper.h"


int get_host_ipv4(void *buf) {
   struct ifaddrs *ifaddr, *ifa;
   int family, s, flags;
   int found = 0;

   if (getifaddrs(&ifaddr) == -1) {
      perror("getifaddrs");
      exit(EXIT_FAILURE);
   }

   /* Got through linked list, look for first matching interface */
   for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
      if (ifa->ifa_addr == NULL) {
         continue;
      }

      family = ifa->ifa_addr->sa_family;
      flags = ifa->ifa_flags;

      /* check if interface matches our needs;
       *    -is the correct family
       *    -is active/running
       *    -is not loopback
       * */
      if ((family == AF_INET) && (flags & IFF_RUNNING) && !(flags & IFF_LOOPBACK)) {
         found = 1;
         memcpy(buf, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, IPv4_LEN);
         char *i = (char *)buf;
         char *j = &((char *)buf)[3];
         char temp;
         while(i < j) {
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
         }

         break;
      }
   }

   freeifaddrs(ifaddr);
   if(found) {
      return(0);
   } else {
      return(-1);
   }
}

int get_host_ipv6(void *buf) {
   struct ifaddrs *ifaddr, *ifa;
   int family, s, flags;
   int found = 0;

   if (getifaddrs(&ifaddr) == -1) {
      perror("getifaddrs");
      exit(EXIT_FAILURE);
   }

   /* Got through linked list, look for first matching interface */
   for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
      if (ifa->ifa_addr == NULL) {
         continue;
      }

      family = ifa->ifa_addr->sa_family;
      flags = ifa->ifa_flags;

      /* check if interface matches our needs;
       *    -is the correct family
       *    -is active/running
       *    -is not loopback
       * */
      if ((family == AF_INET6) && (flags & IFF_RUNNING) && !(flags & IFF_LOOPBACK)) {
         found = 1;
         memcpy(buf, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, IPv6_LEN);
         char *i = (char *)buf;
         char *j = &((char *)buf)[3];
         char temp;
         while(i < j) {
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
         }

         break;
      }
   }

   freeifaddrs(ifaddr);
   if(found) {
      return(0);
   } else {
      return(-1);
   }
}
