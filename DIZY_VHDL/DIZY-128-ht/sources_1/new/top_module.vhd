library ieee;
use ieee.std_logic_1164.all;
use ieee.Numeric_Std.all;
--use ieee.numeric_std_unsigned;

entity top_module is
    port(
         key:        in std_logic_vector(0 to 63);
         IV:         in std_logic_vector(0 to 63);
         clk:        in std_logic;
         reset:      in std_logic;
         ciphertext: out std_logic_vector(0 to 31)
    );
end top_module;

architecture behavioral of top_module is
    signal data_state      : std_logic_vector(0 to 159);
    signal data_permuted   : std_logic_vector(0 to 159);
    signal subs_in         : std_logic_vector(0 to 159);
    signal data_substituted: std_logic_vector(0 to 159);
    signal round_counter:    std_logic_vector(0 to 3);
    
    component sub_layer
        port(data_in:  in std_logic_vector(0 to 159);
             data_out: out std_logic_vector(0 to 159)
        );
    end component;
    component perm160
        port(data_in:  in std_logic_vector(0 to 159);
             data_out: out std_logic_vector(0 to 159)
        );
    end component;

begin
    SL: sub_layer port map(
        data_in => subs_in,
        data_out => data_substituted
    );
    
    PL: perm160 port map(
        data_in => data_substituted,
        data_out => data_permuted
    );
    
    subs_in( 0) <= data_state( 0) xor key( 0) xor IV( 0); 
    subs_in( 1) <= data_state( 1) xor key( 1) xor IV( 1) xor round_counter(0);
    subs_in( 2 to 4)  <= data_state( 2 to 4)  xor round_counter(1 to 3);
    
    subs_in( 5) <= data_state( 5) xor key( 2) xor IV( 2); 
    subs_in( 6) <= data_state( 6) xor key( 3) xor IV( 3) xor round_counter(0);
    subs_in( 7 to 9)  <= data_state( 7 to 9)  xor round_counter(1 to 3);
    
    subs_in(10) <= data_state(10) xor key( 4) xor IV( 4); 
    subs_in(11) <= data_state(11) xor key( 5) xor IV( 5) xor round_counter(0);
    subs_in( 12 to 14) <= data_state( 12 to 14) xor round_counter(1 to 3);
    
    subs_in(15) <= data_state(15) xor key( 6) xor IV( 6); 
    subs_in(16) <= data_state(16) xor key( 7) xor IV( 7) xor round_counter(0);
    subs_in( 17 to 19) <= data_state( 17 to 19)xor round_counter(1 to 3);
    
    subs_in(20) <= data_state(20) xor key( 8) xor IV( 8); 
    subs_in(21) <= data_state(21) xor key( 9) xor IV( 9) xor round_counter(0);
    subs_in(22 to 24) <= data_state(22 to 24)  xor round_counter(1 to 3);
    
    subs_in(25) <= data_state(25) xor key(10) xor IV(10); 
    subs_in(26) <= data_state(26) xor key(11) xor IV(11) xor round_counter(0);
    subs_in(27 to 29) <= data_state(27 to 29)  xor round_counter(1 to 3);
    
    subs_in(30) <= data_state(30) xor key(12) xor IV(12); 
    subs_in(31) <= data_state(31) xor key(13) xor IV(13) xor round_counter(0);
    subs_in(32 to 34) <= data_state(32 to 34) xor round_counter(1 to 3);
    
    subs_in(35) <= data_state(35) xor key(14) xor IV(14); 
    subs_in(36) <= data_state(36) xor key(15) xor IV(15) xor round_counter(0);
    subs_in(37 to 39) <= data_state(37 to 39)  xor round_counter(1 to 3); 
     
    subs_in(40) <= data_state(40) xor key(16) xor IV(16); 
    subs_in(41) <= data_state(41) xor key(17) xor IV(17) xor round_counter(0);
    subs_in(42 to 44) <= data_state(42 to 44) xor round_counter(1 to 3);
    
    subs_in(45) <= data_state(45) xor key(18) xor IV(18); 
    subs_in(46) <= data_state(46) xor key(19) xor IV(19) xor round_counter(0);
    subs_in(47 to 49) <= data_state(47 to 49) xor round_counter(1 to 3);
    
    subs_in(50) <= data_state(50) xor key(20) xor IV(20); 
    subs_in(51) <= data_state(51) xor key(21) xor IV(21) xor round_counter(0);
    subs_in(52 to 54) <= data_state(52 to 54) xor round_counter(1 to 3);
    
    subs_in(55) <= data_state(55) xor key(22) xor IV(22); 
    subs_in(56) <= data_state(56) xor key(23) xor IV(23) xor round_counter(0);
    subs_in(57 to 59) <= data_state(57 to 59) xor round_counter(1 to 3);
    
    subs_in(60) <= data_state(60) xor key(24) xor IV(24); 
    subs_in(61) <= data_state(61) xor key(25) xor IV(25) xor round_counter(0);
    subs_in(62 to 64) <= data_state(62 to 64) xor round_counter(1 to 3);
    
    subs_in(65) <= data_state(65) xor key(26) xor IV(26); 
    subs_in(66) <= data_state(66) xor key(27) xor IV(27) xor round_counter(0);
    subs_in(67 to 69) <= data_state(67 to 69) xor round_counter(1 to 3);
    
    subs_in(70) <= data_state(70) xor key(28) xor IV(28); 
    subs_in(71) <= data_state(71) xor key(29) xor IV(29) xor round_counter(0);
    subs_in(72 to 74) <= data_state(72 to 74) xor round_counter(1 to 3);
    
    subs_in(75) <= data_state(75) xor key(30) xor IV(30); 
    subs_in(76) <= data_state(76) xor key(31) xor IV(31) xor round_counter(0);
    subs_in(77 to 79) <= data_state(77 to 79) xor round_counter(1 to 3);
    
    subs_in(80) <= data_state(80) xor key(32) xor IV(32); 
    subs_in(81) <= data_state(81) xor key(33) xor IV(33) xor round_counter(0);
    subs_in(82 to 84) <= data_state(82 to 84) xor round_counter(1 to 3);
    
    subs_in(85) <= data_state(85) xor key(34) xor IV(34); 
    subs_in(86) <= data_state(86) xor key(35) xor IV(35) xor round_counter(0);
    subs_in(87 to 89) <= data_state(87 to 89) xor round_counter(1 to 3);
    
    subs_in(90) <= data_state(90) xor key(36) xor IV(36); 
    subs_in(91) <= data_state(91) xor key(37) xor IV(37) xor round_counter(0);
    subs_in(92 to 94) <= data_state(92 to 94) xor round_counter(1 to 3);
    
    subs_in(95) <= data_state(95) xor key(38) xor IV(38); 
    subs_in(96) <= data_state(96) xor key(39) xor IV(39) xor round_counter(0);
    subs_in(97 to 99) <= data_state(97 to 99) xor round_counter(1 to 3); 
     
    subs_in(100)<= data_state(100) xor key(40) xor IV(40); 
    subs_in(101)<= data_state(101) xor key(41) xor IV(41) xor round_counter(0);
    subs_in(102 to 104) <= data_state(102 to 104) xor round_counter(1 to 3);
    
    subs_in(105)<= data_state(105) xor key(42) xor IV(42); 
    subs_in(106)<= data_state(106) xor key(43) xor IV(43) xor round_counter(0);
    subs_in(107 to 109) <= data_state(107 to 109) xor round_counter(1 to 3);
    
    subs_in(110)<= data_state(110) xor key(44) xor IV(44); 
    subs_in(111)<= data_state(111) xor key(45) xor IV(45) xor round_counter(0);
    subs_in(112 to 114) <= data_state(112 to 114) xor round_counter(1 to 3);
    
    subs_in(115)<= data_state(115) xor key(46) xor IV(46); 
    subs_in(116)<= data_state(116) xor key(47) xor IV(47) xor round_counter(0);
    subs_in(117 to 119) <= data_state(117 to 119) xor round_counter(1 to 3);
 
        subs_in(120)<= data_state(120) xor key(48) xor IV(48); 
    subs_in(121)<= data_state(121) xor key(49) xor IV(49) xor round_counter(0);
    subs_in(122 to 124) <= data_state(122 to 124) xor round_counter(1 to 3);
    
    subs_in(125)<= data_state(125) xor key(50) xor IV(50); 
    subs_in(126)<= data_state(126) xor key(51) xor IV(51) xor round_counter(0);
    subs_in(127 to 129) <= data_state(127 to 129) xor round_counter(1 to 3);
    
    subs_in(130)<= data_state(130) xor key(52) xor IV(52); 
    subs_in(131)<= data_state(131) xor key(53) xor IV(53) xor round_counter(0);
    subs_in(132 to 134) <= data_state(132 to 134) xor round_counter(1 to 3);
    
    subs_in(135)<= data_state(135) xor key(54) xor IV(54); 
    subs_in(136)<= data_state(136) xor key(55) xor IV(55) xor round_counter(0);
    subs_in(137 to 139) <= data_state(137 to 139) xor round_counter(1 to 3);
    
        subs_in(140)<= data_state(140) xor key(56) xor IV(56); 
    subs_in(141)<= data_state(141) xor key(57) xor IV(57) xor round_counter(0);
    subs_in(142 to 144) <= data_state(142 to 144) xor round_counter(1 to 3);
    
    subs_in(145)<= data_state(145) xor key(58) xor IV(58); 
    subs_in(146)<= data_state(146) xor key(59) xor IV(59) xor round_counter(0);
    subs_in(147 to 149) <= data_state(147 to 149) xor round_counter(1 to 3);
    
    subs_in(150)<= data_state(150) xor key(60) xor IV(60); 
    subs_in(151)<= data_state(151) xor key(61) xor IV(61) xor round_counter(0);
    subs_in(152 to 154) <= data_state(152 to 154) xor round_counter(1 to 3);
    
    subs_in(155)<= data_state(155) xor key(62) xor IV(62); 
    subs_in(156)<= data_state(156) xor key(63) xor IV(63) xor round_counter(0);
    subs_in(157 to 159) <= data_state(157 to 159) xor round_counter(1 to 3);
                                      
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                data_state  <= (others => '0');
                round_counter <= "1000";
            else
                data_state(0 to 19)   <= data_permuted(0 to 19); 
                data_state(20 to 39)  <= data_permuted(80 to 99);
                data_state(40 to 59)  <= data_permuted(20 to 39);
                data_state(60 to 79)  <= data_permuted(100 to 119);
                data_state(80 to 99)  <= data_permuted(40 to 59);
                data_state(100 to 119)<= data_permuted(120 to 139);
                data_state(120 to 139)<= data_permuted(60 to 79);
                data_state(140 to 159)<= data_permuted(140 to 159); 
                
                round_counter <= round_counter(1 to 3) & (round_counter(3) XOR round_counter(0));   
            end if;
        end if;
    end process;
   
 --ready_out <= not (round_counter(0) or  round_counter(1) or round_counter(2) or round_counter(3) or round_counter(4)) ;

    process(round_counter)
    begin
        if round_counter = "1000" then 
            ciphertext <= data_state(0 to 31);
        else
            ciphertext <= (others => '0');
        end if;
    end process;
    
end behavioral;