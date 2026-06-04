library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity divider_4bit is
    Port ( 
        CLOCK_50 : in  STD_LOGIC;
        SW       : in  STD_LOGIC_VECTOR (9 downto 0);
        KEY      : in  STD_LOGIC_VECTOR (3 downto 0);
        LEDR     : out STD_LOGIC_VECTOR (9 downto 0);
        HEX0     : out STD_LOGIC_VECTOR (6 downto 0);
		  HEX4     : out STD_LOGIC_VECTOR (6 downto 0);
		  HEX6     : out STD_LOGIC_VECTOR (6 downto 0);
        HEX1     : out STD_LOGIC_VECTOR (6 downto 0)
    );
end divider_4bit;

architecture Behavioral of divider_4bit is
    signal quot, remn : unsigned(3 downto 0);
    signal reg_A : unsigned(7 downto 0);
    signal reg_B : unsigned(7 downto 0);
    signal busy : std_logic := '0';
    signal count : integer range 0 to 4 := 0;

    component SevenSegDecoder
        Port ( data : in STD_LOGIC_VECTOR (3 downto 0); 
               seg : out STD_LOGIC_VECTOR (6 downto 0));
    end component;

begin
    LEDR(0) <= not busy;

    process(CLOCK_50)
        variable temp_A : unsigned(7 downto 0);
    begin
        if rising_edge(CLOCK_50) then
            if KEY(0) = '0' and busy = '0' then
                reg_A <= unsigned("0000" & SW(7 downto 4));
                reg_B <= unsigned("0000" & SW(3 downto 0));
                count <= 0;
                busy <= '1';
            elsif busy = '1' then
                if count < 4 then
                    temp_A := reg_A sll 1;
                    if (temp_A(7 downto 4) >= reg_B(3 downto 0)) then
                        temp_A(7 downto 4) := temp_A(7 downto 4) - reg_B(3 downto 0);
                        temp_A(0) := '1';
                    else
                        temp_A(0) := '0';
                    end if;
                    reg_A <= temp_A;
                    count <= count + 1;
                else
                    quot <= reg_A(3 downto 0);
                    remn <= reg_A(7 downto 4);
                    busy <= '0';
                end if;
            end if;
        end if;
    end process;

    -- OUTPUT DISPLAYS 
    D0: SevenSegDecoder port map(data => std_logic_vector(quot), seg => HEX0); -- Result
    D1: SevenSegDecoder port map(data => std_logic_vector(remn), seg => HEX1); -- Remainder

    -- INPUT DISPLAYS 
    D2: SevenSegDecoder port map(data => SW(3 downto 0), seg => HEX4); -- B Input
    D3: SevenSegDecoder port map(data => SW(7 downto 4), seg => HEX6); -- A Input

end Behavioral;