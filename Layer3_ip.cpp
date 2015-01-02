
#include "Layer3_ip.hpp"
#include <stdio.h>

IP_Hdr::IP_Hdr(char *buf) {
   ip_packet = buf;

   if(ip_packet == NULL) {
      throw("error: IP_Hdr::IP_Hdr(char *buf) - invalid buffer");
      return;
   }
}


IP_Hdr::~IP_Hdr() {

}

char * IP_Hdr::get() {
   return(ip_packet);
}
char * IP_Hdr::get_payload() {
   return(ip_packet + iphdr_len);
}

int IP_Hdr::hdr_len() {
   return(iphdr_len);
}


/* optional settings */
int IP_Hdr::version(uint8_t version) {
   iphdr->version = version;
   return(0);
}
int IP_Hdr::iphdrlen(uint8_t words) {
   iphdr->ihl = words;
   return(0);
}
int IP_Hdr::tos(uint8_t tos) {
   iphdr->tos = tos;
   return(0);
}
int IP_Hdr::frag(int frag) {
   iphdr->frag_off = frag;
   return(0);
}
int IP_Hdr::tot_len(uint16_t total_len) {
   iphdr->tot_len = htobe16(total_len);
   return(0);
}
int IP_Hdr::ttl(uint8_t ttl) {
   iphdr->ttl = ttl;
   return(0);
}
int IP_Hdr::protocol(uint8_t protocol) {
   iphdr->protocol = protocol;
   return(0);
}
int IP_Hdr::check(uint16_t check) {
   iphdr->check = htobe16(check);
   return(0);
}


int IP_Hdr::dest_ip(std::string ipaddr) {
   inet_pton(AF_INET, ipaddr.c_str(), &iphdr->daddr); 
   return(0);
}
int IP_Hdr::dest_ip(uint32_t ipaddr) {
   iphdr->daddr = htobe32(ipaddr);
   return(0);
}
int IP_Hdr::src_ip(std::string ipaddr) {
   inet_pton(AF_INET, ipaddr.c_str(), &iphdr->saddr); 
   return(0);
}
int IP_Hdr::src_ip(uint32_t ipaddr) {
   iphdr->saddr = htobe32(ipaddr);
   return(0);
}


void IP_Hdr::init() {

   iphdr = (struct iphdr *)ip_packet;

   iphdr_len = 20;
   payload_len = 0;

   memset(ip_packet, 0, iphdr_len);

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
