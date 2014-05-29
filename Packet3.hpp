#ifndef PACKET3_HEADER
#define PACKET3_HEADER

/*
 * Class which encapsulates and manages the creation of a level 3 IP packet
 * See method definitions below for details
 *
 * basically, do something like this;
 *    class Packet3 packet();
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
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <endian.h>

#define _DEFAULT_PACKET_BUFFER_LEN 1300

class Packet3 {

   public:

      /* Constructor, initialises memory requried for packet - pass in buffer len as
       * argument
       * If no argument is specified, will fall back to a default packet buffer size 
       *
       * This is not the size of the packet that will actually be sent, just the size
       * of the buffer used to house the packet
       *
       * Some default values will be given   
       * */
      Packet3();
      Packet3(int buffer_len);

      ~Packet3();

      /* return buffer that houses the packet */
      char *get_raw_packet();

      /* return pointer to beginning of level 4 payload in the packet buffer */
      char *get_payload();

      /* returns the length of entire packet; the number of bytes to send over wire 
       * If you constructed the packet manually without using these methods, then
       * this value will be invalid */
      int packet_len();

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
      int protocol(int protocol);
      int check(uint16_t check);
      int dest_ip(std::string ipaddr); /* You only have to do this! */
      int dest_ip(uint32_t ipaddr);    /* ...or this */
      int src_ip(std::string ipaddr);
      int src_ip(uint32_t ipaddr);


      char *raw_packet;
      struct iphdr *iphdr;
      int iphdr_len;
      int payload_len; 
      int buf_len;
   private:

      

};

#endif
