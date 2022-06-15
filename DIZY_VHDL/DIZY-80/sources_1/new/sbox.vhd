library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity sbox is
    port(   
        data_in:  in  std_logic_vector(4 downto 0);
        data_out: out std_logic_vector(4 downto 0)
        );
end sbox;

architecture Behavioral of sbox is

--type ram_t  is array (0 to 31) of std_logic_vector(4 downto 0); --31
--signal ram : ram_t := 
--(
--"00000", "00100", "01110", "01001", "01101", "01011", "11110", "11011", "11100", "10100", "10011", "11000", "10111", "11101", "00101", "01100",
--"01111", "10001", "01000", "10101", "00011", "11111", "11001", "00110", "10000", "00010", "10110", "00111", "11010", "01010", "00001", "10010"  
-- );
--
begin

-- data_out <= ram(to_integer(unsigned(data_in)));
 --   data_out(0) <=  (data_in(0) and data_in(1)) xor (data_in(1) and data_in(2)) xor (data_in(1) and data_in(3)) xor (data_in(1) and data_in(4)) xor (data_in(2) and data_in(4)) xor data_in(2)                  xor (data_in(4) and data_in(3)) xor data_in(4);
 --   data_out(1) <=  (data_in(0) and data_in(1)) xor (data_in(0) and data_in(2)) xor (data_in(0) and data_in(4)) xor  data_in(1)                 xor (data_in(2) and data_in(3)) xor (data_in(4) and data_in(3)) xor data_in(4);           
 --   data_out(2) <=  (data_in(0) and data_in(3)) xor  data_in(0)                 xor (data_in(1) and data_in(2)) xor  data_in(1)                 xor (data_in(2) and data_in(3)) xor data_in(2)                  xor data_in(3)                  xor data_in(4);
 --   data_out(3) <=  (data_in(0) and data_in(3)) xor (data_in(0) and data_in(4)) xor (data_in(1) and data_in(2)) xor (data_in(1) and data_in(4)) xor data_in(1)                  xor data_in(2)                  xor data_in(3)                  xor data_in(4);
 --   data_out(4) <=  (data_in(0) and data_in(4)) xor (data_in(1) and data_in(2)) xor  data_in(3);

	       process(data_in)
          begin
              case data_in is
          
              when "00000" => data_out <= "00000";
              when "00001" => data_out <= "00100";
              when "00010" => data_out <= "01110";
              when "00011" => data_out <= "01001";
              when "00100" => data_out <= "01101";
              when "00101" => data_out <= "01011";
              when "00110" => data_out <= "11110";
              when "00111" => data_out <= "11011";
              when "01000" => data_out <= "11100";
              when "01001" => data_out <= "10100";
              when "01010" => data_out <= "10011";
              when "01011" => data_out <= "11000";
              when "01100" => data_out <= "10111";
              when "01101" => data_out <= "11101";
              when "01110" => data_out <= "00101";
              when "01111" => data_out <= "01100";
              when "10000" => data_out <= "01111";
              when "10001" => data_out <= "10001";
              when "10010" => data_out <= "01000";
              when "10011" => data_out <= "10101";
              when "10100" => data_out <= "00011";
              when "10101" => data_out <= "11111";
              when "10110" => data_out <= "11001";
              when "10111" => data_out <= "00110";
              when "11000" => data_out <= "10000";
              when "11001" => data_out <= "00010";
              when "11010" => data_out <= "10110";
              when "11011" => data_out <= "00111";
              when "11100" => data_out <= "11010";
              when "11101" => data_out <= "01010";
              when "11110" => data_out <= "00001";
              when "11111" => data_out <= "10010";
              when others => null; -- GHDL complains without this statement
              end case;
          end process;
end Behavioral;