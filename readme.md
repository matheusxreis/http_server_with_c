# Multithreading HTTP server in C

A no so complex http server done in C language. 

This server:
 - Listening TCP connections;
 - has HTTP protocol implementation;
 - has functions and structs that abstract and handle request and response;
 - Handling multiple requests throught a multithreading processing; 
 

### The final view got this way:

![final view](images/finalview.png)

The programmer only pass the PORT and HOST in listen function, and create the routes throught get, post, put and delete functions. Each method function receive a path and a callback, which must receive a request and return a response.

![controllers](images/controllers.png)

### Multithreading vs Singlethreading:

Multithreading        |  Singlethreading
:-------------------------:|:-------------------------:
![multi threading](images/multithreading.gif) | ![single threading](images/singlethread.gif)

That's all folks!

![totodile](https://i.makeagif.com/media/8-22-2016/OJ4YUQ.gif)

