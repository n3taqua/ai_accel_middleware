module mac3(
    input [7:0] in1,
    input [7:0] in2,
    input [7:0] in3,
    input [7:0] w1,
    input [7:0] w2,
    input [7:0] w3,
    output [15:0] out
);
assign out = (in1 * w1) + (in2 * w2) + (in3 * w3);
endmodule
