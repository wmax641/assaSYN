
#include <iostream>

#include <arpa/inet.h>
#include <sys/socket.h>


#include "Layer3_ip.hpp"
#include "Layer4_tcp.hpp"

#define _DEFAULT_PACKET_BUFFER_LEN 1000

int main(void) {

   char *buf = (char *)malloc(_DEFAULT_PACKET_BUFFER_LEN);

   try {
      /* Create custom ip packet */
      class IP_Hdr ip_hdr(buf);
      ip_hdr.src_ip("111.111.111.111");
      ip_hdr.dest_ip("222.222.222.222");

      class TCP_Hdr tcp_hdr(buf + ip_hdr.hdr_len());

      int sock;

      /* sendto() requires a dummy address to send to, the actual destination ip adress
       * will be set via Packet::dest_ip() method */
      struct sockaddr_in dummy;
      dummy.sin_family = AF_INET;
      dummy.sin_port = 0;
      inet_pton(AF_INET, "1.2.3.4", (struct in_addr *)&dummy.sin_addr.s_addr);

      /* Create raw socket */
      if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
         perror("error:");
         return(1);
      }

      if(sendto(sock, ip_hdr.get(), ip_hdr.hdr_len(), 0,
                (struct sockaddr *)&dummy, (socklen_t)sizeof(dummy)) < 0) {
         perror("error:");
      }

   } catch (const char *e) {
      std::cerr << "Caught exception" << std::endl;
      std::cerr << e << std::endl;
   }
   return(0);
}
