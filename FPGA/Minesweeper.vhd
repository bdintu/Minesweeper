library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity Minesweeper is
	generic (
		pattern_num	: integer := 15;
		clk_cycle	: integer := 17000000;
		seg_cycle	: integer := 25000000/240;
		baud_cycle	: integer := 25000000/10;
		joy_cycle	: integer := 25000000/5
	);

	port (
		CLK		: in std_logic;
		PB			: in std_logic;
		WAKE		: in std_logic;
		JOY		: in std_logic_vector (4 downto 0);

		BUZ		: out std_logic;

		L			: out std_logic_vector (7 downto 0);
		MN			: out std_logic_vector (7 downto 0);

		SEG		: out std_logic_vector (7 downto 0);
		COM		: out std_logic_vector (3 downto 0);

		STATUS	: out std_logic_vector (4 downto 0);
		STATE		: out std_logic_vector (1 downto 0);

		POSY		: out std_logic_vector (2 downto 0);
		POSX		: out std_logic_vector (2 downto 0)
	);
end Minesweeper;

architecture Behavioral of Minesweeper is
	type StateType is ( Start, selLevel, sendLevel, randTable, loopGame, DrawFrame, Win, Lose);
	signal NextState : StateType;

	type RamType is array(0 to pattern_num, 0 to 35) of integer range 0 to 31;
	signal table, table_pattern : RamType := (
		(0,1,2,3,10,1,0,1,10,10,3,2,1,2,3,2,2,10,1,10,2,1,2,1,2,2,2,10,1,0,10,1,1,1,1,0),	--easy
		(2,2,2,10,2,1,10,10,3,2,10,1,3,10,3,2,2,1,1,1,2,10,1,0,0,1,2,2,1,0,0,1,10,1,0,0),
		(0,0,2,10,2,0,1,1,2,10,2,0,10,2,2,2,2,1,2,3,10,1,2,10,1,10,2,1,2,10,1,1,1,0,1,1),
		(0,1,1,2,1,1,0,2,10,3,10,1,0,3,10,5,2,2,0,3,10,4,10,1,1,3,10,3,1,1,10,2,1,1,0,0),
		(0,1,10,3,2,0,0,1,3,10,10,1,1,1,4,10,4,1,1,10,3,10,2,0,2,2,3,1,1,0,1,10,1,0,0,0),
		(10,1,1,1,1,0,1,2,2,10,2,1,1,2,10,4,10,1,1,10,2,3,10,2,1,1,2,2,2,1,0,0,1,10,1,0),
		
		(2,10,2,1,1,0,10,2,2,10,1,0,1,2,2,2,2,1,0,1,10,2,3,10,1,2,3,10,5,10,1,10,3,10,4,10),	--normal
		(10,10,10,1,0,0,2,3,2,2,1,1,0,1,1,2,10,1,1,2,10,3,2,2,1,10,3,4,10,3,1,1,2,10,10,10),
		(10,3,3,2,2,1,3,10,10,10,3,10,3,10,7,10,4,1,2,10,4,10,3,1,1,1,2,1,2,10,0,0,0,0,1,1),
		(10,2,2,1,1,0,3,10,4,10,1,0,3,10,10,3,2,1,2,10,4,4,10,2,1,2,3,10,10,2,0,1,10,3,2,1),
		(1,2,10,2,1,0,3,10,6,10,3,1,10,10,10,10,10,1,2,5,10,5,2,1,0,2,10,2,0,0,0,1,1,1,0,0),
		(1,2,10,2,1,0,3,10,6,10,3,1,10,10,10,10,10,1,2,5,10,5,2,1,0,2,10,2,0,0,0,1,1,1,0,0),

		(10,2,2,3,10,2,4,10,4,10,10,1,10,10,10,4,3,2,3,10,5,5,10,2,3,4,10,10,10,2,10,10,3,3,2,1),	--hard
		(10,10,10,10,2,1,4,10,6,4,10,1,3,10,5,10,4,2,2,10,4,10,10,1,3,4,4,4,3,2,10,10,10,2,10,1),
		(1,3,10,3,2,1,10,5,10,10,5,10,3,10,10,10,10,3,10,5,10,10,5,10,1,3,10,3,2,10,0,1,1,1,1,1),
		(10,10,10,10,10,10,10,6,4,4,5,10,10,4,10,1,3,10,10,4,1,1,3,10,10,2,0,0,2,10,1,1,0,0,1,1)
	);
	
	signal baud_clk, joy_clk : std_logic := '0';

	signal clk_count	: integer range 1 to clk_cycle := 1;
	signal use_table	: integer range 0 to pattern_num := 0;
	signal first_touc	: integer range 0 to 1 := 0;
	signal timmer_mod	: integer range 0 to 2 := 1;
	signal level		: integer range 0 to 3 := 0;
	signal x, y 		: integer range 0 to 5 := 0;
	signal bcd			: integer range 0 to 9 := 0;

begin

	state_name : process (NextState, WAKE, PB, JOY, CLK, baud_clk, joy_clk, clk_count, timmer_mod) is
		variable flag_lim, flag_bomb : integer := 0;
	begin
		if PB = '1' then
			NextState <= Start;

		elsif CLK'event and CLK='1' then

		case NextState is

			when Start =>
				L <= "00000001";
				MN <= "00000000";
				BUZ <= '0';
				STATE <= "00";	-- send Start
				STATUS <= "00001"; -- send first lerg sudd
				first_touc <= 0;
				timmer_mod <= 1;
				table <= table_pattern;
				level <= 0;
				x <= 0;
				y <= 0;

				if JOY(4)='0' and joy_clk='1' then
					NextState <= selLevel;
				end if;

			when selLevel =>
				L <= "00000010";
				STATE <= "00";	-- send select level
				STATUS <= "00010"; -- send level

				if joy_clk = '1' then
					if JOY(1) = '0' then			-- easy
						level <= 1;
					elsif JOY(0) = '0' then		-- normal
						level <= 2;
					elsif JOY(3) = '0' then		-- hard
						level <= 3;
					end if;
				end if;

				if level=1 or level=2 or level=3 then
					NextState <= sendLevel;
				end if;
				
			when sendLevel =>
				L <= "00000100";
				STATE <= "00";		-- send select level

				if baud_clk = '1' then
					if level = 1 then				-- easy
						STATUS <= "00100"; 		-- send level
						NextState <= randTable;
					elsif level = 2 then			-- normal
						STATUS <= "01000"; 		-- send level
						NextState <= randTable;
					elsif level = 3 then			-- hard
						STATUS <= "10000"; 		-- send level
						NextState <= randTable;
					end if;
				end if;

			when randTable =>
				L <= "00001000";
				if level = 1 then
					use_table <= clk_count mod 6;
					flag_lim := 7;
					flag_bomb := 7;
				elsif level = 2 then
					use_table <= (clk_count mod 6) +6;
					flag_lim := 10;
					flag_bomb := 10;
				elsif level = 3 then
					use_table <= (clk_count mod 4) +12;
					flag_lim := 15;
					flag_bomb := 15;
				end if;

				MN(3 downto 0) <= std_logic_vector(to_unsigned(use_table, 4));

				if baud_clk = '1' then
					STATE <= "01";			-- send draw table parrw parw
					STATUS <= "00000"; 	-- send table space manyyyy
					NextState <= loopGame;
				end if;

			when loopGame =>
				L <= "00010000";

				if baud_clk = '1' then
					STATUS <= "01100";
					POSX <= std_logic_vector(to_unsigned(x, POSX'length));
					POSY <= std_logic_vector(to_unsigned(y, POSY'length));
				end if;

				if joy_clk = '1' then

					if JOY(0) = '0' then		--UP
						if y > 0 then
							MN(7 downto 4) <= "0001";
							-- send  deleteframe x,y
								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								y <= y -1;

							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif JOY(1) = '0' then	--Left
						if x > 0 then
							MN(7 downto 4) <= "0001";
							-- send  deleteframe x,y
								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								x <= x -1;

							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif JOY(2) = '0' then	--Down
						if y < 5 then 
							MN(7 downto 4) <= "0001";
							-- send  deleteframe x,y
								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								y <= y +1;

							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;
					elsif JOY(3) = '0' then	--Right
						if x < 5  then
							MN(7 downto 4) <= "0001";
							-- send  deleteframe x,y
								STATUS <= "01101";
								POSX <= std_logic_vector(to_unsigned(x, POSX'length));
								POSY <= std_logic_vector(to_unsigned(y, POSY'length));
								x <= x +1;

							-- send drawFrame(x,y)
							NextState <= DrawFrame;
						end if;

					elsif JOY(4) = '0' then	--Center
						if first_touc = 0 then
							first_touc <= 1;
							timmer_mod <= 0;
						end if;
						if table(use_table, 6*x + y) = 0 then				-- space
							MN(7 downto 4) <= "0010";
							STATUS <= "00001";	-- send space
							POSX <= std_logic_vector(to_unsigned(x, POSX'length));
							POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							table(use_table, 6*x + y) <= 11;
							NextState <= loopGame;
						elsif	table(use_table, 6*x + y) = 1 or
								table(use_table, 6*x + y) = 2 or
								table(use_table, 6*x + y) = 3 or
								table(use_table, 6*x + y) = 4 or
								table(use_table, 6*x + y) = 5 or
								table(use_table, 6*x + y) = 6 or
								table(use_table, 6*x + y) = 7 or
								table(use_table, 6*x + y) = 8 then		-- number
							MN(7 downto 4) <= "0100";
							STATUS <= std_logic_vector(to_unsigned(table(use_table, 6*x + y) +2, STATUS'length));	-- send space
							POSX <= std_logic_vector(to_unsigned(x, POSX'length));
							POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							table(use_table, 6*x + y) <= 11;
							NextState <= loopGame;
						elsif table(use_table, 6*x + y) = 10 then		-- bomb booomm
							STATUS <= "10000";	-- send bomb
							POSX <= std_logic_vector(to_unsigned(x, POSX'length));
							POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							NextState <= Lose;
						end if;

					elsif WAKE = '1' then
						if first_touc = 0 then
							first_touc <= 1;
							timmer_mod <= 0;
						end if;
						if table(use_table, 6*x + y) < 16 and flag_lim > 0 and not(table(use_table, 6*x + y) = 11) then		-- place flag
							MN(7 downto 4) <= "1000";
							if table(use_table, 6*x + y) = 10 then
								flag_bomb := flag_bomb -1;
							end if;						
							table(use_table, 6*x + y) <= table(use_table, 6*x + y) + 16;

							flag_lim := flag_lim -1;
							STATUS <= "01110";	-- send place flag
							POSX <= std_logic_vector(to_unsigned(x, POSX'length));
							POSY <= std_logic_vector(to_unsigned(y, POSY'length));

							if flag_bomb = 0 then
								NextState <= Win;
							else
								NextState <= loopGame;								
							end if;	

						elsif table(use_table, 6*x + y) >= 16 then	-- rm flag
							MN(7 downto 4) <= "1000";
							table(use_table, 6*x + y) <= table(use_table, 6*x + y) - 16;
							if table(use_table, 6*x + y) = 10 then
								flag_bomb := flag_bomb +1;
							end if;

							flag_lim := flag_lim +1;
							STATUS <= "00000";	-- send rm flag
							POSX <= std_logic_vector(to_unsigned(x, POSX'length));
							POSY <= std_logic_vector(to_unsigned(y, POSY'length));
							NextState <= loopGame;
						end if;

					end if;
				end if;

			when drawFrame =>
				L <= "00100000";
				if baud_clk = '1' then
					STATUS <= "01100";
					POSX <= std_logic_vector(to_unsigned(x, POSX'length));
					POSY <= std_logic_vector(to_unsigned(y, POSY'length));
					NextState <= loopGame;
				end if;

			when Win =>
				L <= "01000000";
				if baud_clk = '1' then
					STATE <= "10";
					STATUS <= "00000";
				end if;

				timmer_mod <= 2;
				BUZ <= '1';

				if JOY(4)='0' and joy_clk='1' then
					NextState <= Start;
				end if;

			when Lose =>
				L <= "10000000";
				if baud_clk = '1' then
					STATE <= "10";
					STATUS <= "00001";
				end if;

				timmer_mod <= 2;
				BUZ <= '1';

				if JOY(4)='0' and joy_clk='1' then
					NextState <= Start;
				end if;

			when others =>
				L <= "11111111";
		end case;

		end if;
	end process state_name;

	timmer : process(CLK, clk_count, timmer_mod) is
		variable digit_count	: integer range 0 to seg_cycle := 0;

		variable s0 : integer range 0 to 10 := 0;
		variable s1 : integer range 0 to 6  := 0;
		variable m0 : integer range 0 to 10 := 0;
		variable m1 : integer range 0 to 6  := 0;
	begin

			if CLK'event and CLK = '1' then
			
				if timmer_mod = 0 then
					clk_count <= clk_count + 1;
					if clk_count = clk_cycle then
						s0 := s0 + 1;
					end if;

				elsif timmer_mod = 1 then
					s0 := 0;
					s1 := 0;
					m0 := 0;
					m1 := 0;
				end if;

				if s0 = 10 then
					s0 := 0;
					s1 := s1 + 1;
				elsif s1 = 6 then
					s1 := 0;
					m0 := m0 + 1;
				elsif m0 = 10 then
					m0 := 0;
					m1 := m1 + 1;
				elsif m1 = 6 then
					m1 := 0;
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

	clkdiv_baud : process (CLK) is
		variable count : integer range 0 to baud_cycle := 0;
	begin
		if CLK'event and CLK='1' then
			count := count + 1;
			if count = baud_cycle then
				baud_clk <= '1';
			else
				baud_clk <= '0';
			end if;
		end if;
	end process clkdiv_baud;

	clkdiv_joy : process (CLK, JOY) is
		variable count : integer range 0 to joy_cycle := 0;
	begin
		if CLK'event and CLK='1' then
			count := count + 1;
			if count = joy_cycle then
				joy_clk <= '1';
			else
				joy_clk <= '0';
			end if;
		end if;
	end process clkdiv_joy;

	SEG(6 downto 0) <=	"1101111" when BCD = 9 else -- 9
								"1111111" when BCD = 8 else -- 8
								"0000111" when BCD = 7 else -- 7
								"1111101" when BCD = 6 else -- 6
								"1101101" when BCD = 5 else -- 5
								"1100110" when BCD = 4 else -- 4
								"1001111" when BCD = 3 else -- 3
								"1011011" when BCD = 2 else -- 2
								"0000110" when BCD = 1 else -- 1
								"0111111";

end Behavioral;