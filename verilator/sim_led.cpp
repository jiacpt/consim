#include "Vled.h"
#include "Vled___024root.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void step_and_dump_wave(VerilatedContext *contextp, VerilatedVcdC *tfp, Vled *led)
{
    led->eval();
    tfp->dump(contextp->time());
    contextp->timeInc(1);
}

int main()
{
    VerilatedContext *contextp = new VerilatedContext;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    Vled *led = new Vled;

    contextp->traceEverOn(true);
    led->trace(tfp, 0);
    // tfp->open("dump1.vcd");

    led->clk = 0;
    bool led_state = led->io_v;
    step_and_dump_wave(contextp, tfp, led);

    uint32_t cnt = 0;
    while (!contextp->gotFinish())
    {
        led->clk ^= 1;
        step_and_dump_wave(contextp, tfp, led);

        if (led_state != led->io_v)
        {
            printf("[tc:%010ld]led state changed: %d -> %d\n", contextp->time() / 2, led_state, led->io_v);
            cnt++;
            if (cnt == 10)
            {
                break;
            }
            led_state = led->io_v;
        }
    }

    step_and_dump_wave(contextp, tfp, led);
    tfp->close();
    delete tfp;
    delete led;
    delete contextp;
    return 0;
}
