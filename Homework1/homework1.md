## Question A

For the first 1 million reads, the total CPU time it takes to initialize (fill up) the array is **7 seconds** and the RAM usage is about **251 MB**. For the total 36 million reads, the estimated CPU time is **7*36=252 seconds** and estimated RAM usage is about **251*36=9036 MB**. 

![](./QQ截图20210213230540.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 1</center>

![](./QQ截图20210213230436.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 2</center>

## Question B

For the entire 36 million reads, the RAM usage is about **8.91 GB** (shown in Question A) and the CPU time is about **20 seconds**.

![](./QQ截图20210213234637.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 3</center>

Compared with the previously estimated time, there is a big gap. In order to understand why there's such a big mismatch, the code in **test.cpp** was used to test.

You may use the following commands to compile and run the code in a Linux system computer:

```bash
cd /home/yg336/inf503/homework1
g++ -o test.out test.cpp
sbatch test.sh
```

The results are shown in the following figure:

![](./QQ截图20210213234309.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 4</center>

From the figure we know that if we just allocate memories for the reads, the time consumption will increase linearly. However, if we write data into memories, the time consumption will not increase linearly. Comparing these two processes, we can know that **the time it takes to read data from a file and write to memory is uncertain and that will possibly lead to inaccurate estimation.**

If we compare the results from **test.cpp** to the results shown in Fig. 3, we can get another process that may influence the CPU time consumption: **creating the FASTA_readset object**.

## Question C

![](./QQ截图20210217145013.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 5</center>


## Question D

![](./QQ截图20210213235936.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 6</center>

From Fig. 6 we can know that it takes **1606 ms** to deallocate the  memories. It makes sense. The time increases linearly when comparing with the time shown in Fig. 1.

## Question E

The quick sort was used to sort the segments, so the time complexity is O(nlogn). The first 20 lines are:

![](./QQ截图20210214001404.jpg)
<center style="font-size:14px;color:#000000;text-decoration:underline">Fig. 7</center>

