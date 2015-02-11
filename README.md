# CS2016-Labs
Labs for CS2016 - Concurrent Systems and Operating Systems

**_This_** is an ongoing lab

~~**This**~~ is a completed lab

## ~~Lab 1 (1% of Final Mark)~~
[Compute Pi Using Threads](https://www.scss.tcd.ie/CourseModules/CS2016/Assets/Practicals/p1/practical.pdf)

+ Write a complete threaded program in C (or non-OO C++) on a Linux
machine (e.g. stoker.cs.tcd.ie) to compute the value of pi. You'll need to find some way
to do this with, for instance, a series or an integral so that you can use an embarrassingly
parallel approach.

+ Find out how to measure elapsed time in the Linux environment and do some measurements. From the measurements, can you deduce how many processors/cores are in the
machine?

+ Does using more threads make the program complete more quickly? Why or why not (can you explain it?)

## _Lab 2 (3% of Final Mark)_ 
[Producer-Consumer & Condition Variables](https://www.scss.tcd.ie/CourseModules/CS2016/Assets/Practicals/p2/practical.pdf)


Write a complete threaded program in C (or non-OO C++) on a Linux machine (e.g. stoker.cs.tcd.ie) 
to implement a simulated producer, a number of simulated consumers and 
a simulated buffer of limited capacity connecting the producer to the consumers.
Use condition variables to prevent buffer overflow and underflow. Use a thread for the
producer and for each consumer.

Basically the idea is that the producer 'produces' items that are placed in the buffer as
they are produced, so long as the buffer is not already full. If the buffer is full, the producer
must wait until space becomes available in it. The consumer 'consumes' items by removing
them from the buffer and 'using' them. If the buffer is empty, then the consumer must wait,
using a condition variable, until an item becomes available.
Use condition variables for signalling between the producer and consumers - do not use
sleep-wait polling anywhere.

+ Devise and implement scenarios and to show that neither overflow nor underflow occurs.
+ Show also that use of processor time is minimised.
+ Explain whether the consumers are treated "fairly" - if so, how; if not, why not.

The exact details of the items and of their production and consumption are not important,
and can be simulated as follows:

+ The items themselves don't actually have to exist, but the number
of items in the buffer does need to be simulated. It can be an integer. `Adding` and `Removing` items
could be simulated by incrementing or decrementing the number of items in the buffer.
+ Production and consumption of an item could be simulated by a pseudo-random delay
in the producer or consumer at the point of `production` or `consumption`.

## Lab 3 - _TBA_

## Lab 4 - _TBA_

## Lab 5 - _TBA_
