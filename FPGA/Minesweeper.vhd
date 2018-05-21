library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity Minesweeper is
	generic (
		pattern_num	: integer := 2-1;
		clk_cycle	: integer := 2000000;
		baud_cycle	: integer := 2000000/100;
		joy_cycle	: integer := 1000000
	);

	port (
		CLK		: in std_logic;
		JOY		: in std_logic_vector (4 downto 0);

		L			: out std_logic_vector (7 downto 0);
		MN			: out std_logic_vector (7 downto 0);
		STATE		: out std_logic_vector (1 downto 0);
		STATUS	: out std_logic_vector (4 downto 0);
		POSX		: out std_logic_vector (2 downto 0);
		POSY		: out std_logic_vector (2 downto 0)
	);
end Minesweeper;

architecture Behavioral of Minesweeper is
	type StateType is ( Start, waitStartGame, selLevel, bomb, Win, Lose);
	signal State : StateType;

	type RamType is array(0 to pattern_num, 0 to 35) of integer range 0 to 15;
	signal table : RamType := (
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 )
	);

	subtype countpattern_type is integer range 0 to 9;
	signal seed : countpattern_type := 0;
	signal seedxxx : countpattern_type := 0;

	signal level : integer range 0 to 3 := 0;
	signal use_table : integer range 0 to pattern_num := 0;
	
	signal x, y : integer range 0 to 5 := 2;

	signal is_send, clk_clk, baud_clk, joy_clk : std_logic := 0;

begin

	L <= "11111111";
	MN <= "11111111";

	state_name : process (State) is
	begin
		case State is

			when Start =>
				STATE <= "00";	-- send Start
				if (JOY(4)='1') then
					State <= selLevel;
				end if;

			when selLevel =>			
				STATE <= "01";	-- send select level
				level <= 1 when JOY(2) = '1' else
							2 when JOY(1) = '1' else
							3 when JOY(0) = '1' else
							0;
				if (levle=1 or level=2 or level=3) then
					seedxxx <= seed;
					State <= randTable;
				end if;

			when randTable =>
			
				if (level=1) then
					use_table <= seedxxx;
				elsif (level=2) then
					use_table <= seedxxx +10;
				elsif (level=3) then
					use_table <= seedxxx +20;
				end if;
				
				STATE <= "10";	-- send draw table parrw parw
				State <= loopGame;
				
			when loopGame =>
			
				if (joy_clk='1') then
					if (JOY(0)='1') then		--UP
						if ( y > 0 ) then
							-- send  deleteframe x,y
							STATUS <= "01100";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
							y <= y -1;
							-- send drawFrame(x,y)
							STATUS <= "01101";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						end if;
					elsif (JOY(1)='1')then	--Left
						if ( x > 0 ) then 
							-- send  deleteframe x,y
							STATUS <= "01100";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
							x <= x -1;
							-- send drawFrame(x,y)
							STATUS <= "01101";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						end if;
					elsif (JOY(2)='1')then	--Down
						if ( y < 5 ) then 
							-- send  deleteframe x,y
							STATUS <= "01100";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
							y <= y +1;
							-- send drawFrame(x,y)
							STATUS <= "01101";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						end if;
					elsif (JOY(3)='1')then	--Right
						if ( x < 5 ) then 
							-- send  deleteframe x,y
							STATUS <= "01100";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
							x <= x +1;
							-- send drawFrame(x,y)
							STATUS <= "01101";
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						end if;
					elsif (JOY(4)='1')then	--Center

						if (table(level, 5*x + y) = 0) then				-- space
							STATUS <= "00001";	-- send space
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						elsif (	table(level, 5*x + y) = 1 or
									table(level, 5*x + y) = 2 or
									table(level, 5*x + y) = 3 or
									table(level, 5*x + y) = 4 or
									table(level, 5*x + y) = 5 or
									table(level, 5*x + y) = 6 or
									table(level, 5*x + y) = 7 or
									table(level, 5*x + y) = 8 ) then		-- number
							STATUS <= std_logic_vector(unsigned(table(level, 5*x + y) +2));	-- send space
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						elsif (table(level, 5*x + y) = 15) then		-- bomb booomm
							STATUS <= "10000";	-- send space
							POSX <= std_logic_vector(unsigned(x));
							POSY <= std_logic_vector(unsigned(y));
						end if;
					end if;
				end if;
				
				
				if (State=Win) then
					State <= Win;
				else
					State <= Lose;
				end if;
				
			when Win =>
				State <= Start;
			
			when Lose =>
				State <= Start;
		
			when others =>
				State <= StartA;
		end case;
	end process state_name;

	clkdiv_clk : process (CLK) is
		variable count : integer range 0 to clk_cycle := 0;
	begin 
		if (CLK'event and CLK='1') then
			count := count + 1;
			if (count = clk_cycle_10ms) then
				clk_clk <= '1';
			else
				clk_clk <= '0';
			end if;
		end if;
	end process clkdiv_clk;

	clkdiv_send : process (CLK) is
		variable count : integer range 0 to baud_cycle := 0;
	begin
		if (CLK'event and CLK='1') then
			count := count + 1;
			if (count = baud_cycle) then
				baud_clk <= '1';
			else
				baud_clk <= '0';
			end if;
		end if;
	end process clkdiv_send;
	
	clkdiv_joy : process (CLK) is
		variable count : integer range 0 to joy_cycle := 0;
	begin
		if (CLK'event and CLK='1') then
			count := count + 1;
			if (count = joy_cycle) then
				joy_clk <= '1';
			else
				joy_clk <= '0';
			end if;
		end if;
	end process clkdiv_joy;
	
	send_parallel : process (baud_clk) is
	begin
		if (baud_clk'event and baud_clk='1' and is_send='1') then
			--STATUS <= "1111";
			--POSX <= "111";
			--POSY <= "111";
		end if;
	end process send_parallel;
	
	seed_name : process (CLK) is
		variable count : countpattern_type := 0;
	begin
		if (CLK'event and CLK='1') then
			count := count + 1;
		end if;
		seed <= count;
	end process seed_name;

end Behavioral;