// IMPORT NEEDED PACKAGES
import java.util.*;

public class P1 {
    public static void main(String args[]) throws InterruptedException {
        // Create BoundedBuffer of type Request
        BoundedBuffer<Request> bufferQueue = new BoundedBuffer<Request>(5);

        // Create Producer
        Producer prod = new Producer(bufferQueue);

        // Create scanner to read user input
        Scanner sc = new Scanner(System.in);
        // Ask user for how many consumer threads are needed and save to variable
        System.out.println("How many consumer threads are there?");
        int numCon = sc.nextInt();

        // Create Consumers
        Consumer[] con = new Consumer[numCon];
        for(int i = 0;i < con.length;i++) {
            con[i] = new Consumer(bufferQueue,i+1);
        }

        // Create Producer thread
        Thread prodThread = new Thread(prod);

        // Create Consumer threads
        Thread[] conThreads = new Thread[numCon];
        for(int i = 0;i < conThreads.length;i++) {
            conThreads[i] = new Thread(con[i]);
        }

        // Start all threads
        prodThread.start();
        for(int i = 0;i < conThreads.length;i++) {
            conThreads[i].start();
        }

        // Join all threads
        prodThread.join();
        for(int i = 0;i < conThreads.length;i++) {
            conThreads[i].join();
        }

        // Close scanner
        sc.close();
    }
}

// Class to create Request object
class Request {
    // Initialise needed variables
    int reqID;
    int length;
    // Constructor
    public Request(int id,int time) {
        reqID = id;
        length = time;
    }
}

class BoundedBuffer<T> {
    // Initialise needed variables
    private final Object[] buffer;
    private int prodPos,conPos,count;
    // Initialise monitors
    private final Object prodMonitor = new Object();
    private final Object conMonitor = new Object();

    // Constructor
    public BoundedBuffer(int bound) {
        buffer = new Object[bound];
    }

    // Produce method and helper method
    public void produce(Request req) {
        synchronized(prodMonitor) {
            try {
                while(isFull()) {
                    prodMonitor.wait();
                }
            }catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        doProduce(req);
        synchronized(conMonitor) {
            conMonitor.notifyAll();
        }
    }
    protected void doProduce(Request req) {
        buffer[prodPos] = req;
        if(++prodPos == buffer.length) {
            prodPos = 0;
        }
        ++count;
    }

    // Consume method and helper method
    public Request consume() {
        synchronized(conMonitor) {
            try {
                while(isEmpty()) {
                    conMonitor.wait();
                }
            }catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        Request req = doConsume();
        synchronized(prodMonitor) {
            prodMonitor.notifyAll();
        }
        return req;
    }
    protected Request doConsume() {
        Request req = (Request)buffer[conPos];
        if(++conPos == buffer.length) {
            conPos = 0;
        }
        --count;
        return req;
    }

    // Additional helper methods
    public boolean isFull() {
        return count == buffer.length;
    }
    public boolean isEmpty() {
        return count == 0;
    }
}

class Producer implements Runnable {
    // Initialise BoundedBuffer variable
    BoundedBuffer<Request> queue;
    int maxTime = 10;
    int minTime = 1;
    int reqId = 0;
    // Constructor
    public Producer(BoundedBuffer<Request> bbuff) {
        this.queue = bbuff;
    }
    // Run method from Runnable
    public void run() {
        long startTime = System.currentTimeMillis();
        while(true) {
            try {
                reqId++;
                Random rand = new Random();
                Request newReq = new Request(reqId,rand.nextInt(((maxTime+1)-minTime)+minTime));
                queue.produce(newReq);
                long currTime = System.currentTimeMillis();
                float timeElapsed = (currTime-startTime)/1000F;
                System.out.printf("Producer: Produced request ID %d, length %d seconds at time %f.%n", newReq.reqID,newReq.length,timeElapsed);
                System.out.println("Sleeping for 1 second.");
                Thread.sleep(1000);
            }catch(InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Consumer implements Runnable {
    // Initialise needed variables
    BoundedBuffer<Request> queue;
    int conId;
    // Constructor
    public Consumer(BoundedBuffer<Request> bbuff,int id) {
        this.queue = bbuff;
        this.conId = id;
    }
    // Run method from Runnable
    public void run() {
        long startTime = System.currentTimeMillis();
        while(true) {
            try {
                Request conReq = queue.consume();
                long currTime = System.currentTimeMillis();
                float timeElapsed = (currTime-startTime)/1000F;
                System.out.printf("Consumer %d: Assigned request ID %d, processing request for the next %d seconds, current time is %f.%n",conId,conReq.reqID,conReq.length,timeElapsed);
                Thread.sleep(conReq.length*1000);
                currTime = System.currentTimeMillis();
                timeElapsed = (currTime-startTime)/1000F;
                System.out.printf("Consumer %d: Completed request ID %d at time %f.%n",conId,conReq.reqID,timeElapsed);
            }catch(InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}