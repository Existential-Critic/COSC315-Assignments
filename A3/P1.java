// IMPORT NEEDED PACKAGES
import java.util.*;

public class P1 {
    public static void main(String args[]) throws InterruptedException {
        // Create scanner to read user input
        Scanner sc = new Scanner(System.in);
        // Ask user for how many consumer threads are needed and save to variable
        System.out.println("How many consumer threads are there?");
        int numCon = sc.nextInt();

        // Create queue
        final Queue q = new Queue();

        // Create producer thread
        Thread prod = new Thread(
            new Runnable() {
                @Override
                public void run() {
                    try {
                        q.produce();
                    }catch(InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        );

        // Create array of consumer threads
        Thread[] con = new Thread[numCon];
        // Fill consumer array with consumer threads
        for(int i = 0;i < con.length;i++) {
            final int conId = i;
            con[i] = new Thread(
                new Runnable() {
                    int id = conId;
                    @Override
                    public void run() {
                        try {
                            q.consume(id);
                        }catch(InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            );
        }

        // Start all threads
        prod.start();
        for(int i = 0;i<con.length;i++) {
            con[i].start();
        }

        // Finish all threads
        prod.join();
        for(int i = 0;i<con.length;i++) {
            con[i].join();
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

class Queue {
    // Initialise needed variables
    LinkedList<Request> list = new LinkedList<>();
    int capacity = 5;
    long startTime = System.currentTimeMillis();

    // Producer function
    public void produce() throws InterruptedException {
        int id = 0;
        int maxTime = 10;
        int minTime = 1;
        int range = (maxTime-minTime+1);
        Random rand = new Random();
        while(true) {
            synchronized(this) {
                // If list is at capacity, wait
                while(list.size() == capacity) {
                    wait();
                }
                // Create request to be added
                Request req = new Request(id,rand.nextInt(range+minTime));
                // Increment id
                id++;
                // Get current time
                long curTime = System.currentTimeMillis();
                // Get time elapsed in seconds
                float elapsedTime = (curTime - startTime)/1000F;
                // Print producer message
                System.out.printf("Producer: Produced request ID %d, length %d seconds at time %f.%n",req.reqID,req.length,elapsedTime);
                // Add the request to the list
                list.add(req);
                // Notify the consumer threads they can consume
                notify();
                // Notify user about producer sleeping
                System.out.println("Producer: sleeping for 5 seconds");
                Thread.sleep(5000);
            }
        }
    }

    // Consumer function
    public void consume(int conId) throws InterruptedException {
        while(true) {
            synchronized(this) {
                // If list is empty, wait
                while(list.size() == 0) {
                    wait();
                }
                // Retrieve first request in the list
                Request req = list.removeFirst();
                // Get current time
                long curTime = System.currentTimeMillis();
                // Get time elapsed in seconds
                float elapsedTime = (curTime - startTime)/1000F;
                // Print consumer message
                System.out.printf("Consumer %d: Assigned request ID %d, processing request for the next %d seconds, current time is %f.%n",conId,req.reqID,req.length,elapsedTime);
                // Sleep for the duration of the request
                Thread.sleep(req.length*1000);
                // Get current time
                curTime = System.currentTimeMillis();
                // Get time elapsed in seconds
                elapsedTime = (curTime - startTime)/1000F;
                // Print final consumer method
                System.out.printf("Consumer %d: Completed request ID %d at time %f.%n",conId,req.reqID,elapsedTime);
                // Wake the producer thread
                notify();
                // Sleep consumer thread
                Thread.sleep(30000);
            }
        }
    }
}