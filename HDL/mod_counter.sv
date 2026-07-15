module mod_counter
	#(parameter N = 4)
	(
	input logic clk, rst,
	input logic [N-1:0] MAX,
	input logic en,
	output logic [N-1:0] count,
	output logic max_tick
	);
	logic[N-1:0] c, c_nxt;
	always_ff@(posedge clk, posedge rst) begin
		if(rst)
			c <= 0;
		else
			if(en)
			c <= c_nxt;
	end
	assign c_nxt = (c == (MAX -1))? 0:c+1;
	assign count =c;
	assign max_tick = (c == MAX-1)? 1'b1: 1'b0;
endmodule

