#include "Vuart.h"
#include "Vuart___024root.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void step_and_dump_wave(VerilatedContext *contextp, VerilatedVcdC *tfp, Vuart *uart)
{
    uart->eval();
    tfp->dump(contextp->time());
    contextp->timeInc(1);
}

int main()
{
    VerilatedContext *contextp = new VerilatedContext;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    Vuart *uart = new Vuart;

    contextp->traceEverOn(true);
    uart->trace(tfp, 0);
    tfp->open("uart.vcd");

    uart->clk = 0;
    uart->rst = 1;
    step_and_dump_wave(contextp, tfp, uart);
    uart->rst = 0;

    uint32_t cnt = 0;
    while (!contextp->gotFinish())
    {
        uart->clk ^= 1;
        step_and_dump_wave(contextp, tfp, uart);

        if (contextp->time() > 200000)
            break;
    }

    step_and_dump_wave(contextp, tfp, uart);
    tfp->close();
    delete tfp;
    delete uart;
    delete contextp;
    return 0;
}
