`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/09/2026 01:36:44 PM
// Design Name: 
// Module Name: sseg_en
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sseg_en_par
	#(parameter N = 4)(
    input logic [2:0] sel,
    input logic [N-1:0] num_0,
    input logic [N-1:0] num_1,
    input logic [N-1:0] num_2,
    input logic [N-1:0] num_3,
    input logic [N-1:0] num_4,
    input logic [N-1:0] num_5,
    input logic [N-1:0] num_6,
    input logic [N-1:0] num_7,
    output logic [7:0] enb_LEDS,
    output logic [N-1:0] num_out
    );
always_comb begin
case(sel)
0:begin
    enb_LEDS = 8'b11111110;
    num_out = num_0;
end
1:begin
    enb_LEDS = 8'b11111101;
        num_out = num_1;
end
2:begin
    enb_LEDS = 8'b11111011;
        num_out = num_2;
end
3:begin
    enb_LEDS = 8'b11110111;
        num_out = num_3;
end
4:begin
    enb_LEDS = 8'b11101111;
        num_out = num_4;
end
5:begin
    enb_LEDS = 8'b11011111;
        num_out = num_5;
end
6:begin
    enb_LEDS = 8'b10111111;
        num_out = num_6;
end
7:begin
    enb_LEDS = 8'b01111111;
        num_out = num_7;
end
default:begin
    enb_LEDS = 8'b01111111;
        num_out = 0;
end
endcase
end
endmodule
