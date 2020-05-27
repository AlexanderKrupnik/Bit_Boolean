boolean bb(byte *s,unsigned int shift,boolean v) {  // storage is byte[] (between 8 & 65536 (unsigned int) bits, in byte increments)                    
  if (v)                                            // shift=11 is third bit of the second byte; shift=924 is 5th bit of the 116th byte   
    *(s + shift/8) |=  (1 << (shift % 8));          //  set bit in "shift" location    
  else
    *(s + shift/8) &= ~(1 << (shift % 8));          // clear bit in "shift" location 
  return v;  
}

boolean bb(byte *s,unsigned int shift) {         //  get boolean bit form byte[] by bit-position up to unsigned int (65536)
   return *(s + shift/8) & (1 << (shift % 8));      
}
