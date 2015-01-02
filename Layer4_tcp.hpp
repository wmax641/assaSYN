/*
 * 
 *
 *
 */

#ifndef LAYER4_TCP_HEADER
#define LAYER4_TCP_HEADER


#include <netinet/tcp.h>
#include <stdint.h>
#include <string.h>

#include "Layer3_ip.hpp"


class TCP_Hdr {

   public:

      /* Constructor - pass in malloc'd memory buffer. Make sure it's long enough to
       * house the ip_hdr,  tcp_hdr and any payload 
       * 
       * The memory address you pass in will the the beginning of the ip header
       * Also pass in the size of the ip header so we know where the tcp header begins
       *
       * For example;
       *    class TCP_Hdr tcp_hdr(buf,  ip_hdr.hdr_len());
       * 
       * */
      TCP_Hdr(char *buf, int header_begin);
      ~TCP_Hdr();

      char *get();
      char *get_payload();
      int hdr_len();

      /* Set various fields in tcp header
       *
       * Calling TCP_Hdr::init() will set defaults for a SYN packet 
       * It also calculates and sets the TCP checksum
       */
      void init();
      void th_sport(uint16_t port);
      void th_dport(uint16_t port);
      void th_seq(uint32_t number);
      void th_ack(uint32_t number);
      void th_off(uint8_t offset);
      void th_flags(uint8_t flags);
      void th_win(uint16_t win);
      void th_sum(uint16_t sum);
      void th_urp(uint16_t urp);

      /* Recalculates tcp checksum of the tcp_hdr. This needs to be called if you changed
       * values manually.
       * */
      void recalculate_checksum();
       
   private:

      char *ip_packet;
      char *tcp_packet;
      struct tcphdr *tcphdr;
      struct iphdr *iphdr;
      int tcphdr_len;
      int payload_len; 

      uint16_t calculate_tcp_checksum();

};


#endif
