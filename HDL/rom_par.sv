`timescale 1ns / 1ps

module rom_par#(parameter string memory = "foo.mem", parameter DW = 8, parameter AW = 8)(
    input logic clk, ctof,
    input logic [AW-1:0] addr,
    output logic [((DW<<1)-1):0] data
    );
    (* rom_style = "block" *)logic [DW-1:0] rom [0:((1<<AW)-1)];
    initial
        $readmemb(memory, rom);
        
    always_ff@(posedge clk)begin
            data <= rom[addr];
    end
endmodule

