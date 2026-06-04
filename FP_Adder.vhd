library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity fp_adder is
    Port (
        clk    : in  std_logic;
        reset  : in  std_logic;                    
        start  : in  std_logic;                    
        A_in   : in  std_logic_vector(31 downto 0);
        B_in   : in  std_logic_vector(31 downto 0);
        result : out std_logic_vector(31 downto 0);
        done   : out std_logic                     
    );
end fp_adder;

architecture Behavioral of fp_adder is

    type state_type is (IDLE, ALIGN, ADD, NORMALIZE, ROUND, FINISH);
    signal state : state_type := IDLE;

    
    signal s_a, s_b, s_res : std_logic;
    signal e_a, e_b, e_res : unsigned(7 downto 0);
    signal m_a, m_b        : unsigned(23 downto 0); 
    signal m_res           : unsigned(23 downto 0);
    signal sum_ext         : unsigned(24 downto 0); 

begin

    process(clk, reset)
        variable exp_diff : integer;
    begin
        if reset = '1' then
            state <= IDLE;
            done  <= '0';
            result <= (others => '0');
        elsif rising_edge(clk) then
            case state is

                when IDLE =>
                    done <= '0';
                    if start = '1' then
                
                        s_a <= A_in(31);
                        e_a <= unsigned(A_in(30 downto 23));
                        m_a <= unsigned('1' & A_in(22 downto 0));
                        
                        s_b <= B_in(31);
                        e_b <= unsigned(B_in(30 downto 23));
                        m_b <= unsigned('1' & B_in(22 downto 0)); 
                        
                        state <= ALIGN;
                    end if;

                when ALIGN =>
                    
                    if e_a > e_b then
                        exp_diff := to_integer(e_a - e_b);
                        e_res <= e_a;
         
                        if exp_diff > 23 then
                            m_b <= (others => '0');
                        else
                            m_b <= shift_right(m_b, exp_diff);
                        end if;
                    else
                        exp_diff := to_integer(e_b - e_a);
                        e_res <= e_b;
                        
                        if exp_diff > 23 then
                            m_a <= (others => '0');
                        else
                            m_a <= shift_right(m_a, exp_diff);
                        end if;
                    end if;
                    state <= ADD;

                when ADD =>
                    
                    if s_a = s_b then
                        sum_ext <= ('0' & m_a) + ('0' & m_b);
                        s_res   <= s_a;
                    else
                        if m_a >= m_b then
                            sum_ext <= ('0' & m_a) - ('0' & m_b);
                            s_res   <= s_a;
                        else
                            sum_ext <= ('0' & m_b) - ('0' & m_a);
                            s_res   <= s_b;
                        end if;
                    end if;
                    state <= NORMALIZE;

                when NORMALIZE =>
                    
                    if sum_ext(24) = '1' then
                        m_res <= sum_ext(24 downto 1);
                        e_res <= e_res + 1;
                    elsif sum_ext(23) = '0' and sum_ext /= 0 then
                        m_res <= sum_ext(22 downto 0) & '0';
                        e_res <= e_res - 1;
                    else
                        m_res <= sum_ext(23 downto 0);
                    end if;
                    state <= ROUND;

                when ROUND =>
                    
                    state <= FINISH;

                when FINISH =>
                    
                    result <= s_res & std_logic_vector(e_res) & std_logic_vector(m_res(22 downto 0));
                    done   <= '1';
                    if start = '0' then
                        state <= IDLE;
                    end if;

                when others =>
                    state <= IDLE;

            end case;
        end if;
    end process;

end Behavioral;
