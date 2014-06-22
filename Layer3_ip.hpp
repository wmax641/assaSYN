#ifndef LAYER3_IP_HEADER 
#define LAYER3_IP_HEADER

/*
 * Class which encapsulates and manages the creation of a level 3 IP packet
 * See method definitions below for details
 *
 * basically, do something like this;
 *    class IP_Hdr packet();
 *    packet.dest_ip("1.2.3.4");
 *    packet.src_ip("123.123.123.123");
 *    sendto(socket, packet.get_raw_packet(), packet.packet_len(), ...);
 *
 * */

#include "ip_helper.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <endian.h>


class IP_Hdr {

   public:

      /* Constructor - pass in malloc'd memory buffer. Make sure it's long enough to
       * house the ip hdr and any payload (tcp or whatever)
       * 
       * The memory address you pass in will the the beginning of the ip header
       *    which is not necessarily the beginning of the buffer
       *
       * */
      IP_Hdr(char *buf);

      ~IP_Hdr();

      /* return buffer that houses the packet, so it returns a pointer to the
       * address you passed into the constructor */
      char *get();

      /* return pointer to beginning of level 4 payload in the packet buffer */
      char *get_payload();

      /* returns the length of the ip hdr ONLY*/
      int hdr_len();

      /* Set various fields in IP header 
       *
       * When class is instantiated, some useable defaults are automatically set 
       * by calling Packet::init() internally in the constructor. You only have to 
       * set the destination ip address by calling Packet::dest_ip(ipaddr) yourself
       * and not worry about any of the other fields unless;
       *    - You don't want your own IPaddr as source address for IP packet, then
       *      by all means, use Packet::src_ip(ipaddr)
       *    - You didn't add a payload with provided method, instead you did something
       *      like writing bytes directly into buffer
       * */
      void init(); /* Fills up the packet with some default values as described above */

      int version(uint8_t version);
      int iphdrlen(uint8_t words);  /* header length in words(4 bytes) */
      int tos(uint8_t tos);
      int frag(int frag);
      int tot_len(uint16_t total_len);
      int ttl(uint8_t ttl);
      int protocol(uint8_t protocol);
      int check(uint16_t check);
      int dest_ip(std::string ipaddr); /* You only have to do this! */
      int dest_ip(uint32_t ipaddr);    /* ...or this */
      int src_ip(std::string ipaddr);
      int src_ip(uint32_t ipaddr);


   private:

      char *ip_packet;
      struct iphdr *iphdr;
      int iphdr_len;
      int payload_len; 
      int buf_len;
      

};

#endif
