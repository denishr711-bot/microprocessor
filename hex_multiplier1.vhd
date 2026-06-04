library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity hex_multiplier1 is
    port (
        SW   : in  std_logic_vector(17 downto 0); -- Switches
        HEX6 : out std_logic_vector(6 downto 0);  -- Display A
        HEX4 : out std_logic_vector(6 downto 0);  -- Display B
        HEX1 : out std_logic_vector(6 downto 0);  -- Product High Nibble
        HEX0 : out std_logic_vector(6 downto 0)   -- Product Low Nibble
    );
end hex_multiplier1;

architecture Behavioral of hex_multiplier1 is

    function to_7seg(hex : std_logic_vector(3 downto 0)) return std_logic_vector is
    begin
        case hex is
            when x"0" => return "1000000";
            when x"1" => return "1111001";
            when x"2" => return "0100100";
            when x"3" => return "0110000";
            when x"4" => return "0011001";
            when x"5" => return "0010010";
            when x"6" => return "0000010";
            when x"7" => return "1111000";
            when x"8" => return "0000000";
            when x"9" => return "0010000";
            when x"A" => return "0001000";
            when x"B" => return "0000011";
            when x"C" => return "1000110";
            when x"D" => return "0100001";
            when x"E" => return "0000110";
            when x"F" => return "0001110";
            when others => return "1111111";
        end case;
    end function;

    signal A, B : unsigned(3 downto 0);
    signal P    : unsigned(7 downto 0);

begin

    A <= unsigned(SW(7 downto 4)); 
    B <= unsigned(SW(3 downto 0)); 
    
    P <= A * B;

    HEX6 <= to_7seg(std_logic_vector(A));
    HEX4 <= to_7seg(std_logic_vector(B));
    HEX1 <= to_7seg(std_logic_vector(P(7 downto 4)));
    HEX0 <= to_7seg(std_logic_vector(P(3 downto 0)));

end Behavioral;
