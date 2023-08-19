module core (
    input wire clk,
    input wire rst,
    output wire [7:0] seg
);
  reg [3:0] num;


  always @(posedge clk or posedge rst) begin
    if (rst) begin
      num <= 0;
    end else begin
      num <= num + 1;
    end
  end

  assign seg[3:0] = num[3:0];

endmodule

