
//* @title led_blink
//* @author leo
module led (
    input  wire clk,  //* 50M HZ
    input  wire rst,  //* 复位io_v
    output reg  io_v  //* 输出
);

  //* 计数器
  reg [15:0] count;


  //* 自动计数10000，后反转`io_v`
  always @(posedge clk) begin : proc1
    if (rst) begin
      io_v  <= 0;
      count <= 0;
    end else if (count >= 10000) begin
      io_v  <= ~io_v;
      count <= 0;
    end else begin
      count <= count + 1;
    end
  end

endmodule

