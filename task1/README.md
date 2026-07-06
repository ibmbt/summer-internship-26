# Task1

## Requirements

Before proceeding, ensure the following requirements are met:

#### Step 1: Build and Install BLIS

Configure, build, and install BLIS. By default, BLIS will auto-detect the architecture and optimize accordingly. Optionally, you can specify an architecture for better performance during the configuration process.

```bash
./configure auto
make -j8    # Use -j8 or the number of cores you want to use for compilation
sudo make install
```

#### Step 2: Set the Library Path

After installing BLIS, you need to add the BLIS shared library path so that it can be found by linker.

#### Step 3: Run the Program

For ease of use Makefile present that helps compile and run the program. 

### Build and Run

Compile blis_benchmark.c
```bash
make
```
Compile the code and run it with the 8 threads injected.
```bash
make run
```
Clean everything
```bash
make clean
```
## Approach

- initializes random square matrix of sizes from 2k to 18k, use monotonic clock to calculate the time taken.
- use formula ```n^3``` to get flops needed
- use the needed flops and time takes to calculate how many gflops

### Why is there a "warm-up" run?
Before recording the official benchmark times, the program executes a single 4000x4000 matrix multiplication. This acts as a hardware warm-up phase. 

Modern processors aggressively drop clock speeds and put unused cores to sleep (C-States) to save power. When a heavy workload is suddenly requested, the operating system and CPU require a few milliseconds to un-park threads, boost voltages, and ramp up to maximum frequency. By absorbing this "wake-up latency" with a dummy calculation upfront, the actual benchmark loop measures the true, sustained capability of the processor with zero initial latency penalties.

## Results

- if run on single core it produces around 30 gflops.
- when ran on all cores glops increases by number of cores.
- factors like free memory, no bg processes, heating, laptop battery mode (saving, performance etc) affects teh results dramatically.
- ideally run it when laptop in performance mode, plugged in, freshly booted with no tasks sharing memory to achieve best possible results which came out to be arou 275 gflops.
- tracked temp to plot relation which came out to be inverse, as temp increases glops decrease and vise versa.
- when ran back to back, the temperature stabalizes at around 86 degrees and the glops around 220 glops.
- the results were checked against max theoretical and %age effeciency calculated which was around 70%
