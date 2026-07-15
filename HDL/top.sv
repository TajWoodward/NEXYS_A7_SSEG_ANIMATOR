`timescale 1ns / 1ps

module top#(parameter string memory = "foo.mem", parameter DW = 64, parameter AW = 7)(
	input logic clk,
	output logic [7:0] sseg,
	output logic [7:0] AN
    );
    logic sel_count, frame_tick, tick;
    logic [2:0] sel;
    logic [7:0] num_wire;
    logic [AW-1:0] count;
    logic [DW-1:0] data;
    mod_counter #(.N(20)) sel_tick (.clk(clk),.MAX(20'h186a0),.en(1'b1),.max_tick(sel_count));
    mod_counter #(.N(4)) sel_in (.clk(sel_count),.MAX(4'h8),.en(1'b1),.count(sel),.max_tick(tick));
    mod_counter #(.N(32)) fps (.clk(tick),.MAX(32'd50),.en(1'b1),.max_tick(frame_tick));
    mod_counter #(.N(AW)) frame (.clk(frame_tick),.MAX(AW+1),.en(1'b1),.count(count));
    rom_par #(.memory("save_test.mem"),.DW(DW),.AW(AW)) pattern (.clk(clk),.addr(count),.data(data));
    sseg_en_par #(.N(8)) ssegARRAY(
	    .sel(sel),
	    .num_0(data[7:0]),
	    .num_1(data[15:8]),
	    .num_2(data[24:16]),
	    .num_3(data[31:24]),
	    .num_4(data[39:32]),
	    .num_5(data[47:40]),
	    .num_6(data[55:48]),
	    .num_7(data[63:56]),
	    .enb_LEDS(AN),
	    .num_out(sseg)
	    );
endmodule
