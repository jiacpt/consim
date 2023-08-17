module led(
        input  clk,
        output io_v
    );

    /**********计时部分**********/
    //parameter clk_frequency = 27_000_000; // 时钟频率为27Mhz
    parameter count_value       = 7_499_999;

    reg [23:0]  count_value_reg ;
    reg         count_value_flag;

    always @(posedge clk) begin
        if ( count_value_reg <= count_value ) begin
            count_value_reg  <= count_value_reg + 1'b1;
            count_value_flag <= 1'b0 ;
        end
        else begin //计数到 0.5S 了
            count_value_reg  <= 24'b0;
            count_value_flag <= 1'b1 ;
        end
    end
    reg io_v_reg = 1'b0;

    /**********电平翻转部分**********/
    always @(posedge clk) begin
        if ( count_value_flag )
            io_v_reg <= ~io_v_reg;
        else //  电平翻转标志无效
            io_v_reg <= io_v_reg;
    end


    /**********补充一行代码**********/
    assign io_v = io_v_reg;

endmodule
