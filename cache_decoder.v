module cache_decoder (
    input  wire        clk,
    input  wire [31:0] address,
    output reg  [19:0] tag,
    output reg  [7:0]  index,
    output reg  [3:0]  blk_offset
);

always @(posedge clk) begin

    tag <= address[31:12];

    index <= address[11:4];

    blk_offset <= address[3:0];

end

endmodule