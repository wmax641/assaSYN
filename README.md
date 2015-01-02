Generic tcp syn flooder with ip spoofing

This is made as an example of how custom/raw IP packets can be done in C/C++

Won't work on Windows because... Microsoft

IP spoofing won't actually work if you're behind and NAT. 
And any ISPs worth their salt will detect a source ip.addr that doesn't 
belong to their address space and refuse to forward it.

Go wild!! Do whatever you want with this

Instructions (if you want to use this beyond educational purposes):
  * uncomment while(1) loop in assaSYN.cpp
  * make, run ./main
  * ??
