assaSYN by wmax641

Generic tcp syn flooder with ip spoofing

This is made as an example of how custom/raw IP packets can be done in C

Won't work on Windows because... Microsoft

IP spoofing won't actually work if you're behind and NAT. 
And any ISPs worth their salt (as in, not shifty Russian ones) will detect a source 
ip.addr that doesn't belong to their address space and refuse to forward it.

Go wild!! Do whatever you want with this

