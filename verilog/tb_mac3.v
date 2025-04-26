module tb_mac3();
reg [7:0] in1, in2, in3;
reg [7:0] w1, w2, w3;
wire [15:0] out;

mac3 uut (.in1(in1), .in2(in2), .in3(in3), .w1(w1), .w2(w2), .w3(w3), .out(out));

initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, tb_mac3);
    
    in1 = 8'd3; w1 = 8'd2;
    in2 = 8'd4; w2 = 8'd1;
    in3 = 8'd5; w3 = 8'd0;
    
    #10;
    $display("Output: %d", out);
    #10 $finish;
end
endmodule
