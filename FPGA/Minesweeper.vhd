library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity Minesweeper is
	generic (
		pattern_num	: integer := 30-1;
		seed_num		: integer := 9;
		clk_cycle	: integer := 25000000;
		seg_cycle	: integer := 25000000/240;
		baud_cycle	: integer := 25000000/10;
		joy_cycle	: integer := 25000000/5
	);

	port (
		CLK		: in std_logic;
		PB			: in std_logic;
		JOY		: in std_logic_vector (4 downto 0);

		L			: out std_logic_vector (7 downto 0);
		MN			: out std_logic_vector (7 downto 0);

		SEG		: out std_logic_vector (7 downto 0);
		COM		: out std_logic_vector (3 downto 0);

		STATE		: out std_logic_vector (1 downto 0);
		STATUS	: out std_logic_vector (4 downto 0);
		POSX		: out std_logic_vector (2 downto 0);
		POSY		: out std_logic_vector (2 downto 0)
	);
end Minesweeper;

architecture Behavioral of Minesweeper is
	type StateType is ( Start, selLevel, randTable, DrawFrame, loopGame, Win, Lose);
	signal NextState : StateType;

	type RamType is array(0 to pattern_num, 0 to 35) of integer range 0 to 15;
	signal table : RamType := (
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 ),
		(0,1,2,3,15,1,  0,1,15,15,3,2,   1,2,3,2,2,15,  1,15,2,1,2,1,  2,2,2,15,1,0,  15,1,1,1,1,0 ),
		(2,2,2,15,2,1,  15,15,3,2,15,1,  3,15,2,2,2,1,  1,1,2,15,1,0,  0,1,2,2,1,0,   0,1,15,1,0,0 )
	);

	signal seed : integer range 0 to seed_num := 0;
	signal seedxxx : integer range 0 to seed_num := 0;

	signal level : integer range 0 to 3 := 0;
	signal use_table : integer range 0 to pattern_num := 0;

	signal bcd	: std_logic_vector (3 downto 0) := "0000";

	signal is_send, baud_clk, joy_clk : std_logic := '0';
	
	signal x, y : integer range 0 to 5 := 0;

	signal signal_joy : std_logic_vector (4 downto 0);

begin

	signal_joy <= JOY;
	MN(4 downto 0) <= signal_joy;
	
	MN(7) <= baud_clk;

	state_name : process (NextState, PB, CLK, baud_clk, joy_clk) is
	begin
		if PB='1' then
			NextState <= Start;

		elsif CLK'event and CLK='1' then

		case NextState is

			when Start =>
				L <= "00000001";
				STATE <= "00";	-- send Start
				STATUS <= "00001"; -- send first lerg sudd
				level <= 0;
				MN(6 downto 5) <= "01";

				if JOY(4)='0' and joy_clk='1' then
					MN(6 downto 5) <= "01";
					NextState <= selLevel;
				else
					NextState <= Start;
				end if;

			when selLevel =>
				L <= "00000010";
				STATE <= "00";	-- send select level
				STATUS <= "00010"; -- send level

				if joy_clk='1' then
					if JOY(1)='0' then			--easy
						level <= 1;
					elsif JOY(0)='0' then		--normal
						level <= 2;
					elsif JOY(3)='0' then		--hard
						level <= 3;
					end if;
				end if;

				if level=1 or level=2 or level=3 then
					seedxxx <= seed;
					NextState <= randTable;
				else
					NextState <= selLevel;
				end if;

			when randTable =>
				L <= "00000100";
				if (level=1) then
					use_table <= seedxxx;
				elsif (level=2) then
					use_table <= seedxxx +10;
				elsif (level=3) then
					use_table <= seedxxx +20;
				end if;
				
				STATE <= "01";	-- send draw table parrw parw
				STATUS <= "00000"; -- send table space manyyyy
				NextState <= loopGame;

			when drawFrame =>
				if baud_clk = '1' then
					STATUS <= "01100";
					POSX <= std_logic_vector(to_unsigned(x, POSX'length));
					POSY <= std_logic_vector(to_unsigned(y, POSY'length));
				end if;
				NextState <= loopGame;

			when loopGame =>
				L <= "00001000";

				if baud_clk = '1' then
					STATUS <= "01100";
					POSX <= std_logic_vector(to_unsigned(x, POSX'length));
					POSY <= std_logic_vector(to_unsigned(y, POSY'length));
				end if;

				if (joy_clk='1') then
					if (JOY(0)='0') then		--UP
						if ( y > 0 ) then
							--MN <= "00000001";
							-- send  deleteframe x,y

								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								y <= y -1;

							
							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif (JOY(1)='0')then	--Left
						if ( x > 0 ) then
							--MN <= "00000010";
							-- send  deleteframe x,y

								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								x <= x -1;

							
							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif (JOY(2)='0')then	--Down
						if ( y < 5 ) then 
							--MN <= "00000100";
							-- send  deleteframe x,y

								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								y <= y +1;
		
							
							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif (JOY(3)='0')then	--Right
						if ( x < 5 ) then 
							--MN <= "00001000";
							-- send  deleteframe x,y

								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								x <= x +1;
							
							
							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif (JOY(4)='0')then	--Center
						if (table(level, 5*x + y) = 0) then				-- space
							--MN <= "10000000";
							if baud_clk = '1' then
								STATUS <= "00001";	-- send space
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							end if;
							NextState <= loopGame;
						elsif (	table(level, 5*x + y) = 1 or
									table(level, 5*x + y) = 2 or
									table(level, 5*x + y) = 3 or
									table(level, 5*x + y) = 4 or
									table(level, 5*x + y) = 5 or
									table(level, 5*x + y) = 6 or
									table(level, 5*x + y) = 7 or
									table(level, 5*x + y) = 8 ) then		-- number
							--MN <= "01000000";
							if baud_clk = '1' then
								STATUS <= std_logic_vector(to_unsigned(table(level, 5*x + y) +2, STATUS'length));	-- send space
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							end if;
							NextState <= loopGame;
						elsif (table(level, 5*x + y) = 15) then		-- bomb booomm
							--MN <= "00100000";
							if baud_clk = '1' then
								STATUS <= "10000";	-- send space
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							end if;
							NextState <= Lose;
						end if;
					end if;
				end if;

				--if (NextState=Win) then
		--			NextState <= Win;
		--		else
		--			NextState <= Lose;
		--		end if;
		--		
		--	when Win =>
		--		L <= "00010000";
		--		NextState <= Start;

		--	when Lose =>
		--		L <= "00100000";
		--		NextState <= Start;

			when others =>
				MN(6 downto 5) <= "00";
				--NextState <= Start;
		end case;
		
		end if;
	end process state_name;

	timmer : process(CLK) is
		variable sec_count	: integer range 0 to clk_cycle := 0;
		variable digit_count	: integer range 0 to seg_cycle := 0;

		variable s0		: std_logic_vector (3 downto 0) := "0000";
		variable s1		: std_logic_vector (3 downto 0) := "0000";
		variable m0		: std_logic_vector (3 downto 0) := "0000";
		variable m1		: std_logic_vector (3 downto 0) := "0000";
	begin

			if CLK'event and CLK = '1' then

				sec_count := sec_count + 1;
				if sec_count = clk_cycle then
					s0 := s0 + 1;
				end if;

				if s0 = "1010" then
					s0 := "0000";
					s1 := s1 + 1;
				elsif s1 = "0110" then
					s1 := "0000";
					m0 := m0 + 1;
				elsif m0 = "1010" then
					m0 := "0000";
					m1 := m1 + 1;
				elsif m1 = "0110" then
					m1 := "0000";
				end if;

				digit_count := digit_count + 1;				
				if digit_count < seg_cycle/4 then
					BCD <= s0;
					SEG(7) <= '0';
					COM <= "1110";
				elsif digit_count < seg_cycle/2 then
					BCD <= s1;
					SEG(7) <= '0';
					COM <= "1101";
				elsif digit_count < seg_cycle*3/4 then
					BCD <= m0;
					SEG(7) <= '1';
					COM <= "1011";
				elsif digit_count < seg_cycle then
					BCD <= m1;
					SEG(7) <= '0';
					COM <= "0111";
				end if;

			end if;
	end process timmer;

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

	clkdiv_joy : process (CLK, JOY) is
		variable count : integer range 0 to joy_cycle := 0;
	begin
		if CLK'event and CLK='1' and ( JOY(0)='0' or JOY(0)='1' or JOY(0)='1' or JOY(0)='1' or JOY(0)='1' ) then
			count := count + 1;
			if (count = joy_cycle) then
				joy_clk <= '1';
			else
				joy_clk <= '0';
			end if;
		end if;
	end process clkdiv_joy;

	seed_name : process (CLK) is
		variable count : integer range 0 to seed_num := 0;
	begin
		if (CLK'event and CLK='1') then
			count := count + 1;
		end if;
		seed <= count;
	end process seed_name;

	--send_parallel : process (baud_clk) is
	--begin
	--	if (baud_clk'event and baud_clk='1' and is_send='1') then
			--STATUS <= "1111";
			--POSX <= "111";
			--POSY <= "111";
	--	end if;
	--end process send_parallel;

	SEG(6 downto 0) <=	"1101111" when BCD = "1001" else -- 9
								"1111111" when BCD = "1000" else -- 8
								"0000111" when BCD = "0111" else -- 7
								"1111101" when BCD = "0110" else -- 6
								"1101101" when BCD = "0101" else -- 5
								"1100110" when BCD = "0100" else -- 4
								"1001111" when BCD = "0011" else -- 3
								"1011011" when BCD = "0010" else -- 2
								"0000110" when BCD = "0001" else -- 1
								"0111111";

end Behavioral;