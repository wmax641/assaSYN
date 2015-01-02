
#include <stdlib.h>

#include "Layer4_tcp.hpp"
#include <stdio.h>

TCP_Hdr::TCP_Hdr(char *buf, int header_begin) {

   if(ip_packet == NULL) {
      throw("error: IP_Hdr::IP_Hdr(char *buf) - invalid buffer");
      return;
   }

   ip_packet = buf;
   tcp_packet = buf + header_begin;

   tcphdr = (struct tcphdr *)tcp_packet;
   iphdr = (struct iphdr *)buf;

   tcphdr_len = sizeof(struct tcphdr);
   payload_len = 0;
   
}
TCP_Hdr::~TCP_Hdr() {

}

char * TCP_Hdr::get() {
   return(tcp_packet);
}

char * TCP_Hdr::get_payload() {
   return(tcp_packet + tcphdr_len);
}

int TCP_Hdr::hdr_len() {
   return(tcphdr_len);
}


void TCP_Hdr::th_sport(uint16_t port) {
   tcphdr->th_sport = htobe16(port);
}
void TCP_Hdr::th_dport(uint16_t port) {
   tcphdr->th_dport = htobe16(port);
}
void TCP_Hdr::th_seq(uint32_t number) {
   tcphdr->th_seq = htobe32(number);
}
void TCP_Hdr::th_ack(uint32_t number) {
   tcphdr->th_ack = htobe32(number);
}
void TCP_Hdr::th_off(uint8_t offset) {
   tcphdr->th_off = offset;
}
void TCP_Hdr::th_flags(uint8_t flags) {
   tcphdr->th_flags = flags;
}
void TCP_Hdr::th_win(uint16_t win) {
   tcphdr->th_win = htobe16(win);
}
void TCP_Hdr::th_sum(uint16_t sum) {
   tcphdr->th_sum = sum;
}
void TCP_Hdr::th_urp(uint16_t urp) {
   tcphdr->th_urp = htobe16(urp);
}

void TCP_Hdr::init() {
   tcphdr->th_sport = htobe16(5000 + (rand()%55000));
   tcphdr->th_dport = htobe16(80);
   tcphdr->th_seq = rand();
   tcphdr->th_ack = 0;
   tcphdr->th_off = 5;
   tcphdr->th_flags = TH_SYN;
   tcphdr->th_win = htobe16(29200);
   tcphdr->th_urp = 0;
   tcphdr->th_sum = calculate_tcp_checksum();
}

void TCP_Hdr::recalculate_checksum() {
   tcphdr->th_sum = calculate_tcp_checksum();
}

/* See RFC 1071 for IP/TCP checksum calculation */
/* See RFC 793 for TCP specific checksum calculation */
uint16_t TCP_Hdr::calculate_tcp_checksum() {

   /* set checksum to 0 before calculation */
   tcphdr->th_sum = 0;

   int size = tcphdr_len + payload_len;
   unsigned int sum = 0;
   int i;

   /* Calculate checksum for tcp header and payload */
   for(i = 0; i < size - 1; i += 2) {
      uint16_t chunk = *(uint16_t *) &tcp_packet[i];
      sum += chunk;
   }

   /* Calculate checksum for odd byte in payload */
   if(size & 1) {
      uint16_t octet = (uint8_t)tcp_packet[i];
      sum += octet;
   }

   /* Calculate checksum for pseudo header */
   {
# if __BYTE_ORDER == __LITTLE_ENDIAN
      sum += (uint16_t)(iphdr->saddr >> 16); 
      sum += (uint16_t)(iphdr->saddr & 0xffff);
      sum += (uint16_t)(iphdr->daddr >> 16);
      sum += (uint16_t)(iphdr->daddr & 0xffff);
      sum += (uint16_t)(IPPROTO_TCP<< 8);
      sum += (uint16_t)(tcphdr_len + payload_len) << 8;
#endif
# if __BYTE_ORDER == __BIG_ENDIAN
      sum += (uint16_t)(be32toh(iphdr->saddr) >> 16);
      sum += (uint16_t)(be32toh(iphdr->saddr) & 0xffff);
      sum += (uint16_t)(be32toh(iphdr->daddr) >> 16);
      sum += (uint16_t)(be32toh(iphdr->daddr) & 0xffff);
      sum += (uint16_t)(IPPROTO_TCP);
      sum += (uint16_t)(tcphdr_len + payload_len);
#endif
   }

   while(sum >> 16) {
      sum = (sum & 0xffff) + (sum >> 16);
   }
   return(~sum);

}
