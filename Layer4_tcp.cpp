
#include "Layer4_tcp.hpp"

TCP_Hdr::TCP_Hdr(char *buf) {

   tcp_packet = buf;
   tcphdr = (struct tcphdr *)buf;

   tcphdr_len = sizeof(struct tcphdr);
   memset(buf, 1, tcphdr_len);

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


int TCP_Hdr::th_sport(uint16_t port) {
   tcphdr->th_sport = port;
   return(0);
}
int TCP_Hdr::th_dport(uint16_t port) {
   tcphdr->th_dport = port;
   return(0);
}
int TCP_Hdr::th_seq(uint32_t number) {
   tcphdr->th_seq = number;
   return(0);
}
int TCP_Hdr::th_ack(uint32_t number) {
   tcphdr->th_ack = number;
   return(0);
}
int TCP_Hdr::th_off(uint8_t offset) {
   tcphdr->th_off = offset;
   return(0);
}
int TCP_Hdr::th_flags(uint8_t flags) {
   tcphdr->th_flags = flags;
   return(0);
}



int hdr_len();
