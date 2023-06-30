import java.util.concurrent.Semaphore;

public class BoundBufferProblem {

    private static final int BUFFER_SIZE = 5; // total no of peaple eating 
    private static int[] buffer = new int[BUFFER_SIZE]; // array containing them
    private static int numItems = 0; // number of items
    private static int in = 0; // variable for in use person
    private static int out = 0; // for not in use persons
    private static Semaphore mutex = new Semaphore(1);
    private static Semaphore full = new Semaphore(0);
    private static Semaphore empty = new Semaphore(BUFFER_SIZE);

    public static void main(String[] args) {
        // thread is created for produces which is process in our case
        Thread producer = new Thread(() -> {
            while (true) {
                try {
                    empty.acquire();
                    mutex.acquire();
                    int item = (int) (Math.random() * 100);
                    buffer[in] = item;
                    in = (in + 1) % BUFFER_SIZE;
                    numItems++;
                    System.out.println("Produced item: " + item);
                    mutex.release();
                    full.release();
                    Thread.sleep((long) (Math.random() * 1000));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        producer.start();
        // thread for consumer is created which is CPU in our case
        Thread consumer = new Thread(() -> {
            while (true) {
                try {
                    full.acquire();
                    mutex.acquire();
                    int item = buffer[out];
                    out = (out + 1) % BUFFER_SIZE;
                    numItems--;
                    System.out.println("Consumed item: " + item);
                    mutex.release(); 
                    empty.release();
                    Thread.sleep((long) (Math.random() * 1000));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        consumer.start();
    }
}
