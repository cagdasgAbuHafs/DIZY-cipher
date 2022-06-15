
library ieee;
use ieee.std_logic_1164.all;
use IEEE.NUMERIC_STD.ALL;

entity sub_layer is
    port(
         data_in:  in  std_logic_vector(0 to 119);
         data_out: out std_logic_vector(0 to 119)
    );
end sub_layer;

architecture behavioral of sub_layer is
    component sbox
        port(data_in:  in  std_logic_vector(0 to 4);
             data_out: out std_logic_vector(0 to 4)
        );
    end component;
begin
    GEN_SBOXES: for i in 0 to 23 generate
        SX: sbox port map(
            data_in  => data_in (5*i to 5*i+4),
            data_out => data_out(5*i to 5*i+4)
        );
    end generate;
end behavioral;