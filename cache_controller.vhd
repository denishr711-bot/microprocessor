library ieee;
use ieee.std_logic_1164.all;

entity cache_controller is
    port (
        clk  : in std_logic;
        hit  : in std_logic;
        read : out std_logic
    );
end entity cache_controller;

architecture behavioral of cache_controller is
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if hit = '1' then
                read <= '1';
            else
                read <= '0';
            end if;
        end if;
    end process;
end architecture behavioral;
