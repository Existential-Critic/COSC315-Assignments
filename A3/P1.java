public class P1 {
    public static void main(String args[]) {
        System.out.println("Test");
    }
}

class BoundedBuffer<T> {
    private final Object[] buffer;      // Queue data
    private int addPos,removePos,count;   // Start position, end position, count of the queue

    // INITIALISER
    public BoundedBuffer(int bound) {
        // Set buffer to be a new queue
        buffer = new Object[bound];
    }

    // PRIMARY METHODS
    // Method to add to queue, blocks until empty
    public synchronized void add(T object) {
        try {
            while(isFull()) {
                wait();
            }
        } catch(InterruptedException e) {
            e.printStackTrace();
        }
        doAdd(object);
        notifyAll();
    }
    // Method to remove from queue, blocks until full
    public synchronized T remove() {
        try {
            while(isEmpty()) {
                wait();
            }
        } catch(InterruptedException e) {
            e.printStackTrace();
        }
        T element = doRemove();
        notifyAll();
        return element;
    }

    // HELPER METHODS
    // Check if queue is full
    public synchronized boolean isFull() {
        return count == buffer.length;
    }
    // Check if queue is empty
    public synchronized boolean isEmpty() {
        return count == 0;
    }
    // Add helper method
    protected synchronized void doAdd(T object) {
        buffer[addPos] = object;
        if(++addPos == buffer.length) {
            addPos = 0;
        }
        ++count;
    }
    // Remove helper method
    protected synchronized T doRemove() {
        T element = (T)buffer[removePos];
        if(++removePos == buffer.length) {
            removePos = 0;
        }
        --count;
        return element;
    }
}