EVC communicates with this board only using single wire.

The way communication works that example

if EVC needs to send value 200 to this board, the EVC keeps the line pulled up for 
that much time, basically the value is converted into millisecond. So to send 
value 200 the EVC keeps the line pulled up for 200ms.

Now EVC sends 32bit value so this value is converted into 4byte and send that way, therefore
the maximum time the line can be pulled up is for 255ms. 


This is the way to send the value.


Now complete communication is as such

1)  EVC send 1st byte 
2)  EVC wait for 60ms
3)  EVC sends *break pulse of 300ms to indicate 1 byte is sent*
4)  EVC wait for 60ms
5)  EVC send 2nd byte
6)  EVC wait for 60ms
7)  EVC sends *break pulse of 300ms to indicate 1 byte is sent*
8)  EVC wait for 60ms
9)  EVC send 3rd byte
10) EVC wait for 60ms
11) EVC sends *break pulse of 300ms to indicate 1 byte is sent*
12) EVC wait for 60ms
13) EVC send 4th byte
14) EVC wait for 60ms
15) EVC sends *end pulse of 500ms to indicate full data is sent*


Delays can be reduced little bit more to what fits 