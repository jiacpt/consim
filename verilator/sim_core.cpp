#include "Vcore.h"
#include "Vcore___024root.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void step_and_dump_wave(VerilatedContext *contextp, VerilatedVcdC *tfp, Vcore *core)
{
    core->eval();
    tfp->dump(contextp->time());
    contextp->timeInc(1);
}

int main()
{
    VerilatedContext *contextp = new VerilatedContext;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    Vcore *core = new Vcore;

    contextp->traceEverOn(true);
    core->trace(tfp, 0);
    tfp->open("core.vcd");

    core->clk = 0;
    core->rst = 1;
    step_and_dump_wave(contextp, tfp, core);
    core->rst = 0;

    uint32_t cnt = 0;
    while (!contextp->gotFinish())
    {
        core->clk ^= 1;
        step_and_dump_wave(contextp, tfp, core);

        if (contextp->time() > 100000)
            break;
    }

    step_and_dump_wave(contextp, tfp, core);
    tfp->close();
    delete tfp;
    delete core;
    delete contextp;
    return 0;
}
