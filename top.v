module lab1(
input wire [2:0] SW,
output reg [2:0] LED_RED);
always @* begin
LED_RED[0] = 1'b0; // default value is 0
if (SW[0] == 1'b1 && SW[1] == 1'b1) begin
LED_RED[0] = 1'b1;
end else if (SW[0] == 1'b1 && SW[2] == 1'b1) begin
LED_RED[0] = 1'b1;
end else if (SW[1] == 1'b1 && SW[2] == 1'b1) begin
LED_RED[0] = 1'b1;
end
end
endmodule