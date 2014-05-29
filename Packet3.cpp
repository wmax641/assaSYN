
#include "Packet3.hpp"
#include <stdio.h>

Packet3::Packet3() {
   raw_packet = (char *)malloc(_DEFAULT_PACKET_BUFFER_LEN);

   if(raw_packet == NULL) {
      throw("error: Packet3::Packet3(int buf_len) - Could not malloc() buffer");
      return;
   }
   buf_len = _DEFAULT_PACKET_BUFFER_LEN;
   init();
}

Packet3::Packet3(int req_buf_len) {
   if(req_buf_len >= 20) {
      raw_packet = (char *)malloc(req_buf_len);
      if(raw_packet == NULL) {
         throw("error: Packet3::Packet3(int buf_len) - Could not malloc() buffer");
      }
      buf_len = req_buf_len;
      init();

   } else {
      throw("error: Packet3::Packet3(int buf_len) - buf_len must be over 20 bytes");
   }
}

Packet3::~Packet3() {
   if(raw_packet != NULL) {
      free(raw_packet);
   }
}

char * Packet3::get_raw_packet() {
   return(raw_packet);
}
char * Packet3::get_payload() {
   return(raw_packet + iphdr_len);
}

int Packet3::packet_len() {
   return(iphdr_len + payload_len);
}



int Packet3::version(uint8_t version) {

   return(0);
}
int Packet3::iphdrlen(uint8_t words) {
   return(0);
}
int Packet3::tos(uint8_t tos) {
   return(0);
}
int Packet3::frag(int frag) {
   return(0);
}
int Packet3::tot_len(uint16_t total_len) {
   return(0);
}
int Packet3::ttl(uint8_t ttl) {
   return(0);
}
int Packet3::protocol(int protocol) {
   return(0);
}
int Packet3::check(uint16_t check) {
   return(0);
}
int Packet3::dest_ip(std::string ipaddr) {
   return(0);
}
int Packet3::dest_ip(uint32_t ipaddr) {
   iphdr->daddr = htobe32(ipaddr);
   return(0);
}
int Packet3::src_ip(std::string ipaddr) {
   return(0);
}
int Packet3::src_ip(uint32_t ipaddr) {
   iphdr->saddr = htobe32(ipaddr);
   return(0);
}

void Packet3::init() {

   iphdr = (struct iphdr *)raw_packet;

   iphdr_len = 20;
   payload_len = 0;

   memset(raw_packet, 0, buf_len);

   iphdr->version = 4;
   iphdr->ihl = 5;
   iphdr->tos = 0;
   iphdr->frag_off = 0;
   iphdr->ttl = 64;
   iphdr->tot_len = htobe16(20);
   iphdr->protocol = IPPROTO_TCP;
   iphdr->daddr = 0;

   uint32_t my_ipaddr = 0; 
   if(get_host_ipv4(&my_ipaddr)) {
      my_ipaddr = 0;
   }
   iphdr->saddr = htobe32(my_ipaddr);
}
