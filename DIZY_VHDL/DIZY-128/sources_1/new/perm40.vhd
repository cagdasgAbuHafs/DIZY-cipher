library ieee;
use ieee.std_logic_1164.all;
use IEEE.NUMERIC_STD.ALL;

entity perm40 is
    Port ( data_in :  in  STD_LOGIC_VECTOR (0 to 39);
           data_out:  out STD_LOGIC_VECTOR (0 to 39)
          );
end perm40;

architecture behavioral of perm40 is

begin
    --0
    data_out( 0) <= data_in(22)  XOR data_in(2);
    data_out( 1) <= data_in(35)  XOR data_in(8);
    data_out( 2) <= data_in(16)  XOR data_in(28);
    data_out( 3) <= data_in(10);             
    data_out( 4) <= data_in(31);             
    --1                                
    data_out( 5) <= data_in(20)  XOR data_in(7);
    data_out( 6) <= data_in(27)  XOR data_in(13);
    data_out( 7) <= data_in(1)   XOR data_in(33);
    data_out( 8) <= data_in(15);             
    data_out( 9) <= data_in(36);             
    --2                                 
    data_out(10) <= data_in(25)  XOR data_in(12);
    data_out(11) <= data_in(32)  XOR data_in(18);
    data_out(12) <= data_in(6)   XOR data_in(38);
    data_out(13) <= data_in(0);              
    data_out(14) <= data_in(21);             
    --3                                 
    data_out(15) <= data_in(37)  XOR data_in(17);
    data_out(16) <= data_in(26)  XOR data_in(3);
    data_out(17) <= data_in(11)  XOR data_in(23);
    data_out(18) <= data_in(5);              
    data_out(19) <= data_in(30);             
    --4                                 
    data_out(20) <= data_in(27)  XOR data_in(17);
    data_out(21) <= data_in(30)  XOR data_in(9);
    data_out(22) <= data_in(0)   XOR data_in(24);
    data_out(23) <= data_in(11);             
    data_out(24) <= data_in(35);             
    --5                            
    data_out(25) <= data_in(32)  XOR data_in(2);
    data_out(26) <= data_in(36)  XOR data_in(14);
    data_out(27) <= data_in(5)   XOR data_in(29);
    data_out(28) <= data_in(16);
    data_out(29) <= data_in(20);
    --6             
    data_out(30) <= data_in(37)  XOR data_in(7);
    data_out(31) <= data_in(21)  XOR data_in(19);
    data_out(32) <= data_in(10)  XOR data_in(34);
    data_out(33) <= data_in(1);
    data_out(34) <= data_in(25);
    --7              
    data_out(35) <= data_in(22)  XOR data_in(12);
    data_out(36) <= data_in(31)  XOR data_in(4);
    data_out(37) <= data_in(15)  XOR data_in(39);
    data_out(38) <= data_in(6);
    data_out(39) <= data_in(26);

    
end behavioral;