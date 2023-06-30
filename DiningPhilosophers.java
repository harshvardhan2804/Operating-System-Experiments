import java.util.concurrent.Semaphore;

public class DiningPhilosophers {
    private static final int NUM_PHILOSOPHERS = 5; // total number of phiosphers
    private static final Semaphore[] forks = new Semaphore[NUM_PHILOSOPHERS]; // forks created 
    private static final Semaphore maxDiners = new Semaphore(NUM_PHILOSOPHERS - 1); // max number that can eat at a time

    public static void main(String[] args) {
        // creates semaphores  equal to number of philosphers
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            forks[i] = new Semaphore(1); 
        }
        // creates left and right fork for all philosphers
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            int id = i;
            int leftFork = i;
            int rightFork = (i + 1) % NUM_PHILOSOPHERS;
        // threads are created
            Thread philosopher = new Thread(() -> {
                while (true) {
                    try {
                        // Philosopher is thinking
                        Thread.sleep((long)(Math.random() * 1000));

                        // Philosopher is hungry
                        maxDiners.acquire();
                        forks[leftFork].acquire();
                        forks[rightFork].acquire();

                        // Philosopher is eating
                        System.out.println("Philosopher " + id + " is eating");
                        Thread.sleep((long)(Math.random() * 1000));

                        // Philosopher is done eating
                        forks[leftFork].release();
                        forks[rightFork].release();
                        maxDiners.release();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            });
            philosopher.start();
        }
    }
}
