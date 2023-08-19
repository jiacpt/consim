`include "defines.sv"

//* { signal: [
//*   { name: "clk",  wave: "P......" },
//*  { name: "bus",  wave: "x.==.=x", data: ["head", "body", "tail", "data"] },
//*  { name: "wire", wave: "0.1..0." }
//* ],
//*    head:{
//*       text:'WaveDrom example',
//*     tick:0,
//*     every:2
//*   }}

//*{reg: [
//* { "name": "IPO",   "bits": 8, "attr": "RO" },
//*   {                  "bits": 7 },
//*    { "name": "BRK",   "bits": 5, "attr": "RW", "type": 4 },
//*   { "name": "CPK",   "bits": 2 },
//*   { "name": "Clear", "bits": 3 },
//*     { "bits": 8 }
//*]}


//* @title pc_reg
//* @author leo
module pc_reg (
    input  wire                  clk,
    input  wire                  rst,
    input  wire                  jump_flag_i,        //* 这是非常非常多的描述
    input  wire [  `InstAddrBus] jump_addr_i,        //* dawdwadwa
    input  wire [`Hold_Flag_Bus] hold_flag_i,        //* 达瓦
    input  wire                  jtag_reset_flag_i,  //* **ok**
    output reg  [  `InstAddrBus] pc_o
);



  //* @name: pcg
  //* 这个表示连续
  always @(posedge clk) begin
    // 复位
    if (rst == `RstEnable || jtag_reset_flag_i == 1'b1) begin
      pc_o <= `CpuResetAddr;
      // 跳转
    end else if (jump_flag_i == `JumpEnable) begin
      pc_o <= jump_addr_i;
      // 暂停
    end else if (hold_flag_i >= `Hold_Pc) begin
      pc_o <= pc_o;
      // 地址加4
    end else begin
      pc_o <= pc_o + 4'h4;
    end
  end

endmodule


