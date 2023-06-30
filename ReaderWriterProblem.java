import java.util.concurrent.Semaphore;

public class ReaderWriterProblem {
    private static final int BUFFER_SIZE = 100;
    private static final int NUM_READERS = 5;
    private static final int NUM_WRITERS = 2;
    private static int[] buffer = new int[BUFFER_SIZE];
    private static int numItems = 0;

    // Create three semaphores: mutex (for readers/writers access to numItems), writeMutex (for writers to access buffer), and readMutex (for readers to access buffer)
    private static Semaphore mutex = new Semaphore(1);
    private static Semaphore writeMutex = new Semaphore(1);
    private static Semaphore readMutex = new Semaphore(NUM_READERS);

    public static void main(String[] args) {
        Thread[] readers = new Thread[NUM_READERS];
        Thread[] writers = new Thread[NUM_WRITERS];

        // Create threads for readers
        for (int i = 0; i < NUM_READERS; i++) {
            int id = i + 1;
            readers[i] = new Thread(() -> {
                while (true) {
                    try {
                        // Acquire the read mutex
                        readMutex.acquire();

                        // Acquire the mutex to access numItems
                        mutex.acquire();

                        // Read items from buffer and print them out
                        System.out.print("Reader " + id + " is reading " + numItems + " items: ");
                        for (int j = 0; j < numItems; j++) {
                            System.out.print(buffer[j] + " ");
                        }
                        System.out.println();

                        // Release the mutex to access numItems
                        mutex.release();

                        // Release the read mutex
                        readMutex.release();

                        // Sleep for a random amount of time (up to 1 second)
                        Thread.sleep((long)(Math.random() * 1000));
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            });
            readers[i].start();
        }

        // Create threads for writers
        for (int i = 0; i < NUM_WRITERS; i++) {
            int id = i + 1;
            writers[i] = new Thread(() -> {
                while (true) {
                    try {
                        // Acquire the write mutex
                        writeMutex.acquire();

                        // Acquire the mutex to access numItems
                        mutex.acquire();

                        // Generate a random item and add it to the buffer
                        int item = (int)(Math.random() * 100);
                        buffer[numItems] = item;
                        numItems++;

                        // Print out that a writer wrote an item
                        System.out.println("Writer " + id + " wrote item: " + item);

                        // Release the mutex to access numItems
                        mutex.release();

                        // Release the write mutex
                        writeMutex.release();

                        // Sleep for a random amount of time (up to 1 second)
                        Thread.sleep((long)(Math.random() * 1000));
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            });
            writers[i].start();
        }
    }
}
