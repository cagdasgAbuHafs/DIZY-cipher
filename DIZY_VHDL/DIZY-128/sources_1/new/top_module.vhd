library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--use ieee.numeric_std_unsigned;

--use work.util.all;
entity top_module is
    port(
--        plaintext:  in std_logic_vector(0 to 7);
         key:        in std_logic_vector(0 to 1);
         IV:         in std_logic_vector(0 to 1); --IV is 80 bits in total         
         clk:        in std_logic;
         reset:      in std_logic;
         ciphertext: out std_logic_vector(0 to 31)
    );
end top_module;

architecture behavioral of top_module is
    signal data_state: std_logic_vector(0 to 159);

    signal perm_in: std_logic_vector(0 to 39);
    signal perm_out: std_logic_vector(0 to 39);
    
    signal subs_in: std_logic_vector(0 to 4);
    signal subs_out: std_logic_vector(0 to 4);
    
    signal lfsr_counter:  std_logic_vector (5 downto 0);
    signal sig: std_logic_vector(1 downto 0); --00 sbox operation, 01 matrix op, 10 permutation
    
    signal round_counter: std_logic_vector(0 to 3);

    component sbox
    port(   
        data_in:  in  std_logic_vector(4 downto 0);
        data_out: out std_logic_vector(4 downto 0)
        );
    end component;
    component perm40
        port(data_in:  in std_logic_vector(0 to 39);
             data_out: out std_logic_vector(0 to 39)
        );
    end component;

begin
    SL: sbox port map(
        data_in => subs_in,
        data_out => subs_out
    );

    PL: perm40 port map(
        data_in => perm_in,
        data_out => perm_out
    );


    subs_in(0) <= data_state(0) xor IV(0) xor key(0);
    subs_in(1) <= data_state(1) xor IV(1) xor key(1) xor round_counter(0);
    subs_in(2 to 4) <= data_state(2 to 4) xor round_counter(1 to 3);
    perm_in <= data_state(0 to 39);
    
    process(clk, reset)
    begin
        if rising_edge(clk) then
            if reset = '1' then

                data_state  <= (others => '0');
                lfsr_counter  <= "110010";
                round_counter <= "1000";
                sig  <= "00";
            else
                lfsr_counter(5 downto 0) <= lfsr_counter(4 downto 0) & (lfsr_counter(5) XOR lfsr_counter(0));
                if  (sig = "00") then
                    data_state <=  data_state(5 to 159) & subs_out;                
                elsif (sig = "01") then
                    data_state <= data_state(40 to 159) & perm_out;
                else
                    data_state(20 to 39) <= data_state(80 to 99);                   
                    data_state(40 to 59) <= data_state(20 to 39);
                    data_state(60 to 79) <= data_state(100 to 119);
                    data_state(80 to 99) <= data_state(40 to 59);
                    data_state(100 to 119)<= data_state(120 to 139);
                    data_state(120 to 139)<= data_state(60 to 79);
                    round_counter <= round_counter(1 to 3) & (round_counter(3) XOR round_counter(0));
                    lfsr_counter <= "110010";
                    sig  <= "00";
                end if;               
                if (lfsr_counter = "101100") then                  
                    sig <= "01";
                end if;            
                if (lfsr_counter = "001101")  then
                    sig <= "10"; 
                end if;                
            end if;
        end if;
    end process;

    process(round_counter)
    begin
        if round_counter = "1000" then -- and perm_start = '0'
            ciphertext <= data_state(0 to 31);
        else
            ciphertext <= (others => '0');
        end if;
    end process;
    
end behavioral;