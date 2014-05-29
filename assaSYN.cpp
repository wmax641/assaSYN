
#include <iostream>

#include <arpa/inet.h>
#include <sys/socket.h>


#include "Packet3.hpp"


int main(void) {


   try {
      /* Create custom ip packet */
      class Packet3 packet(256);
      packet.src_ip(1);
      packet.dest_ip(2);

      int sock;

      /* sendto() requires a dummy address to send to, the actual destination ip adress
       * will be set via Packet::dummy(dest_ip) method */
      struct sockaddr_in dummy;
      dummy.sin_family = AF_INET;
      dummy.sin_port = 0;
      inet_pton(AF_INET, "1.2.3.4", (struct in_addr *)&dummy.sin_addr.s_addr);

      /* Create raw socket */
      if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
         perror("error:");
         return(1);
      }

      if(sendto(sock, packet.get_raw_packet(), packet.packet_len(), 0,
                (struct sockaddr *)&dummy, (socklen_t)sizeof(dummy)) < 0) {
         perror("error:");
      }

   } catch (const char *e) {
      std::cerr << "Caught exception" << std::endl;
      std::cerr << e << std::endl;
   }
   return(0);
}
