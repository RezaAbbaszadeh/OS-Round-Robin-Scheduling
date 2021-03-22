# OS-Round-Robin-Scheduling
Simulating round robin scheduling algorithm of operating system processes.<br>
Memory allocation strategy is best-fit.

time quantum: 50ms<br>
total memory: 8,000,000 Bytes<br>

### Input
at first number of processes is given and on each next line a process is given in below format:<br>
‫‪```Process_name‬‬ start_time(ms) burst_time(ms) memory_needed(byte)```
start_time is when the process enters ready queue.
```
7
Init 840 210 2
Second 1280 641 2080
First 995 983 890000
Third  1570 820 654000
Sixth 2900 340 1234000
Fourth 1710 1200 4000000
Fifth 2400 900 3000000
```

### Output
Log of every time memory allocated to a proccess or its state changes to 'running'.
```
Init   time:840   memory_addr:0x0   mem_length:0x2   Memory Alocated
Init   time:840   memory_addr:0x0
Init   time:890   memory_addr:0x0
Init   time:940   memory_addr:0x0
Init   time:990   memory_addr:0x0


First   time:1040   memory_addr:0x2   mem_length:0x0949D   Memory Alocated
First   time:1040   memory_addr:0x2
Init   time:1090   memory_addr:0x0
First   time:1100   memory_addr:0x2
First   time:1150   memory_addr:0x2
First   time:1200   memory_addr:0x2
First   time:1250   memory_addr:0x2


Second   time:1300   memory_addr:0x2949D   mem_length:0x028   Memory Alocated
Second   time:1300   memory_addr:0x2949D
First   time:1350   memory_addr:0x2
Second   time:1400   memory_addr:0x2949D
First   time:1450   memory_addr:0x2
Second   time:1500   memory_addr:0x2949D
First   time:1550   memory_addr:0x2
Second   time:1600   memory_addr:0x2949D


Third   time:1650   memory_addr:0x2BC9D   mem_length:0x0BAF9   Memory Alocated
Third   time:1650   memory_addr:0x2BC9D
First   time:1700   memory_addr:0x2
Second   time:1750   memory_addr:0x2949D
Third   time:1800   memory_addr:0x2BC9D


Fourth   time:1850   memory_addr:0x267971   mem_length:0x0090D3   Memory Alocated
Fourth   time:1850   memory_addr:0x267971
First   time:1900   memory_addr:0x2
Second   time:1950   memory_addr:0x2949D
Third   time:2000   memory_addr:0x2BC9D
Fourth   time:2050   memory_addr:0x267971
First   time:2100   memory_addr:0x2
Second   time:2150   memory_addr:0x2949D
Third   time:2200   memory_addr:0x2BC9D
Fourth   time:2250   memory_addr:0x267971
First   time:2300   memory_addr:0x2
Second   time:2350   memory_addr:0x2949D
Third   time:2400   memory_addr:0x2BC9D
Fourth   time:2450   memory_addr:0x267971

Fifth   BLOCKED
First   time:2500   memory_addr:0x2
Second   time:2550   memory_addr:0x2949D
Third   time:2600   memory_addr:0x2BC9D
Fourth   time:2650   memory_addr:0x267971
First   time:2700   memory_addr:0x2
Second   time:2750   memory_addr:0x2949D
Third   time:2800   memory_addr:0x2BC9D
Fourth   time:2850   memory_addr:0x267971


Sixth   time:2900   memory_addr:0x260A45   mem_length:0x054D21   Memory Alocated
Sixth   time:2900   memory_addr:0x260A45
First   time:2950   memory_addr:0x2
Second   time:3000   memory_addr:0x2949D
Third   time:3050   memory_addr:0x2BC9D
Fourth   time:3100   memory_addr:0x267971
Sixth   time:3150   memory_addr:0x260A45
First   time:3200   memory_addr:0x2
Second   time:3250   memory_addr:0x2949D
Third   time:3300   memory_addr:0x2BC9D
Fourth   time:3350   memory_addr:0x267971
Sixth   time:3400   memory_addr:0x260A45
First   time:3450   memory_addr:0x2
Second   time:3500   memory_addr:0x2949D
Third   time:3541   memory_addr:0x2BC9D
Fourth   time:3591   memory_addr:0x267971
Sixth   time:3641   memory_addr:0x260A45
First   time:3691   memory_addr:0x2
Third   time:3741   memory_addr:0x2BC9D
Fourth   time:3791   memory_addr:0x267971
Sixth   time:3841   memory_addr:0x260A45
First   time:3891   memory_addr:0x2
Third   time:3941   memory_addr:0x2BC9D
Fourth   time:3991   memory_addr:0x267971
Sixth   time:4041   memory_addr:0x260A45
First   time:4091   memory_addr:0x2
Third   time:4124   memory_addr:0x2BC9D
Fourth   time:4174   memory_addr:0x267971
Sixth   time:4224   memory_addr:0x260A45
Third   time:4264   memory_addr:0x2BC9D
Fourth   time:4314   memory_addr:0x267971
Third   time:4364   memory_addr:0x2BC9D
Fourth   time:4414   memory_addr:0x267971
Third   time:4464   memory_addr:0x2BC9D
Fourth   time:4514   memory_addr:0x267971
Third   time:4564   memory_addr:0x2BC9D
Fourth   time:4584   memory_addr:0x267971
Fourth   time:4634   memory_addr:0x267971
Fourth   time:4684   memory_addr:0x267971
Fourth   time:4734   memory_addr:0x267971
Fourth   time:4784   memory_addr:0x267971
Fourth   time:4834   memory_addr:0x267971
Fourth   time:4884   memory_addr:0x267971
Fourth   time:4934   memory_addr:0x267971
Fourth   time:4984   memory_addr:0x267971

Fifth   time:5034   memory_addr:0x2BC9D   mem_length:0x0C6CD2   Memory Alocated after process 'Fourth' released memory
Fifth   time:5084   memory_addr:0x2BC9D
Fifth   time:5134   memory_addr:0x2BC9D
Fifth   time:5184   memory_addr:0x2BC9D
Fifth   time:5234   memory_addr:0x2BC9D
Fifth   time:5284   memory_addr:0x2BC9D
Fifth   time:5334   memory_addr:0x2BC9D
Fifth   time:5384   memory_addr:0x2BC9D
Fifth   time:5434   memory_addr:0x2BC9D
Fifth   time:5484   memory_addr:0x2BC9D
Fifth   time:5534   memory_addr:0x2BC9D
Fifth   time:5584   memory_addr:0x2BC9D
Fifth   time:5634   memory_addr:0x2BC9D
Fifth   time:5684   memory_addr:0x2BC9D
Fifth   time:5734   memory_addr:0x2BC9D
Fifth   time:5784   memory_addr:0x2BC9D
Fifth   time:5834   memory_addr:0x2BC9D
Fifth   time:5884   memory_addr:0x2BC9D
```

