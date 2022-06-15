library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity top_module_tb is
end;

architecture bench of top_module_tb is

  component top_module
      port(
           key:        in std_logic_vector(0 to 1);
           IV:        in std_logic_vector(0 to 1);
           clk:        in std_logic;
           reset:      in std_logic;
           ciphertext: out std_logic_vector(0 to 31)
      );
  end component;

  signal key: std_logic_vector(0 to 1);
  signal IV:  std_logic_vector(0 to 1);
  signal clk: std_logic;
  signal reset: std_logic;
  signal ciphertext: std_logic_vector(0 to 31) ;

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: top_module port map ( key        => key,
                             IV         => IV,
                             clk        => clk,
                             reset      => reset,
                             ciphertext => ciphertext );

  stimulus: process
  begin
  
    -- Put initialisation code here
--    wait for 20 ns;
     reset <= '1';
--   key <= X"0123456789ABCDEF0123";
--    plaintext <= X"01";
--    counter <= 0;
    wait for clock_period/2;
    reset <= '0';
    IV <= "00";

    key <= "10";
    wait for clock_period*2;
    key <= "00";
    wait for clock_period*553;
    
    IV <= "01";
    wait for clock_period*4;
    IV <= "00";
    wait for clock_period*551;
    
    stop_the_clock <= false;
    wait;

    -- Put test bench stimulus code here

--    stop_the_clock <= true;
--    wait;
  end process;

  clocking: process
  begin
    while not stop_the_clock loop
      clk <= '0', '1' after clock_period / 2;
      wait for clock_period;
    end loop;
    wait;
  end process;

end;
