# virt-cm3

A virtual Cortex-M3 development environment: QEMU​ or Renode​ replaces the board, so you build, run and debug embedded firmware entirely on the host — no hardware, no probe. One ELF runs on both simulators; printf comes out over semihosting

Board: ARM MPS2-AN385.

## Build

```bash
make                      # -> build/hello.elf
make clean
```

## Run

```bash
make run_qemu             # exit: Ctrl-A then X
make run_renode           # exit: Ctrl-C
```

## Debug

Simulator acts as a GDB server on TCP **3333**:

```bash
make gdbserver_qemu       # or: make gdbserver_renode
make gdbclient            # second terminal
```

Then `break main`, `continue`, `step`, `info registers`.

## Requirements

`arm-none-eabi-gcc`, `arm-none-eabi-gdb`, `qemu-system-arm` and/or `renode`, `make`.
