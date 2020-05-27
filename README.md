# Bit_Boolean
Easy, way to store boolean values in addressable bits, instead of using whole bytes - especially useful for Arduino 

Function name is bb(), stands for Bit Boolean

Advantages:  
     Saves 8x RAM: for boolean storage (except in last byte of array, where some bits may be unused) 
          especially helpful when large number of booleans are needed in a RAM constrained environment like Arduino
     Easy: minimal code overhead and easy syntax in one (overloaded) function 
     Flexible: as needs grow, enlarge bit storage array one byte at a time; just declare a larger array  
     useful as both boolean array substitute, and to replace multiple individual boolean variables (see use cases below)

Disadvantage:
     Speed of execution, takes about x5 longer vs standard boolean variables (due to bit manipulation overhead) still very fast  

Syntax: ~bb(arrayName,unsigned int bitNum [,bool value]) ~ 
        arrayName - pointer to byte array declared for boolean bit storage (the array name is the pointer)   
        bitNum    - the bit-number in the array being addressed  
                 ( e.g.  5 is the 6th bit, of the first byte, 924 - is 5th bit of the 116th byte)
        [value]   - optional, if present, stored in the specified bit; if absent specified bit's value is retrieved       

Usage Overview: 
 declare array of bytes to be used for boolean storage. Each byte allows for storage of 8 individually addressable bits 
 the array can grow as needed in increments of 1 byte up to available memory, or up to byte[8191] 
 (unsigned int bits of < 65,535.) 
 
 returns: boolean value, either bit read, or written (depending on the presence of the third optional parameter)

      bit numbering starts at 0 (0 - 7 per byte) 
      byte numbering in array starts at 0 (like all c/c++ arrays) 
      bitNum = 0; refers to the first bit of the first byte 
      bitNum = 7; refers to the last (8th)  bit of the first byte   
      bitNum = 8; refers to the first bit of the second byte 

sample usage: 
bool a = bb(boolStore,11);    //sets the value of boolean 'a' to the value of the 3rd bit of the second byte of boolStore[];
 int i=924;
bb(boolStore,i,true)          //sets the 924th bit (5th bit of the 116th byte) of the boolStore array to true 
bb(boolStore,5,bb(boolRep,0)) //set the value of the 6th bit of boolStore, to the value of the very first bit of boolRep[]

Generally knowing which bit in which byte is being used unnecessary, just know that for each extra array byte 8 more addressable bits by the bitNum parameter.

      It is the developer's responsibility to not overwrite data outside the boolean storage array bounds 
      by providing an bitNum value that is in-bounds  

Use case 1: use the bitNum just like a boolean array: use bitNum as the array index, boolean[index] 
(to save x8 of bytes of storage) 
         byte a[125]       // byte array of 1000 bits (allowng to store 1000 addressable bits, and save 875 bytes of RAM)
         bool b[1000]      // uses 1000 bytes to store boolean array 
   
Use case 2: use byte array to store boolean data in bits instead of individual boolean variables 
          use constants for readability  
 
  1)    define a byte[] with enough bits to hold all booleans (can be expanded later a byte at a time, as needs grow)

 example :
 boolean      GlobBoolAray[1];   // create a 1 element byte array to store up to 8 boolean values
                       
  2)    instead of defining individual boolean variables, define constants, to represent bit positions in 
            the byte array, (using the names that would have been assigned to the boolean variables) 
            (use const or #define constants use no RAM, they are replaced by the compiler like #define)

 //Example constants to use as array indexes for the binNum parameter: 
 const byte itemRead   = 0;  
 const byte triggerA   = 1; 
 const byte GPSread    = 2;  
 const byte globalMute = 4; 
 etc...

       then use those constants in the bb() as the bitNum (instead of using the independent boolean variable,) 
            bb() will store or read the boolean value in the bit represented by the constant's value 
  
//Examples of bb() sing constants above:  
   bb(GlobBoolAray,triggerA,true);  // sets the second bit (bit #1) to true, as the constant 'triggerA'=1, (instead of using
                                    //   an independent boolean variable called triggerA which would occupy 8 bits) 
    
   if(bb(GlobBoolAray,itemRead))    // if() statement evaluates the bit in itemRead (bit position 0) of GlobBoolArray[]  
   
