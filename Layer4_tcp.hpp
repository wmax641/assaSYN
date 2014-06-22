#ifndef LAYER4_TCP_HEADER
#define LAYER4_TCP_HEADER


#include <netinet/tcp.h>
#include <stdint.h>
#include <string.h>


class TCP_Hdr {

   public:

      /* Constructor - pass in malloc'd memory buffer. Make sure it's long enough to
       * house the tcp hdr and any payload 
       * 
       * The memory address you pass in will the the beginning of the tcp header
       *    which is not necessarily the beginning of the buffer
       *
       * */
      TCP_Hdr(char *buf);
      ~TCP_Hdr();

      char *get();
      char *get_payload();
      int hdr_len();

      int th_sport(uint16_t port);
      int th_dport(uint16_t port);
      int th_seq(uint32_t number);
      int th_ack(uint32_t number);
      int th_off(uint8_t offset);
      int th_flags(uint8_t flags);
/*
       # define TH_FIN	0x01
       # define TH_SYN	0x02
       # define TH_RST	0x04
       # define TH_PUSH	0x08
       # define TH_ACK	0x10
       # define TH_URG	0x20
*/


   private:

      char *tcp_packet;
      struct tcphdr *tcphdr;
      int tcphdr_len;
      int payload_len; 

};


#endif
