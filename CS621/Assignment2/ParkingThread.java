import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

import static java.text.MessageFormat.format;

/**
 * @author anuja
 * @netId: yd1530
 * @created 2/21/21
 */

public class ParkingThread extends Thread{
    Semaphore parkingSemaphore;
    String threadName;
    int carsOnTheLot = 0;
    
    public ParkingThread(Semaphore parkingSemaphore, String threadName){
        super(threadName);
        this.threadName = threadName;
        this.parkingSemaphore = parkingSemaphore;
    }
    
    @Override
    public void run(){
        // uncomment this to run for more than 1 time
        // for(int runner = 0; runner < ThreadLocalRandom.current().nextInt(5); runner++){
        for(int runner = 0; runner < 1; runner++){
    
            // park some cars to begin with
            for(int itr = 0; itr < ThreadLocalRandom.current().nextInt(SemaphoreDriver.parkingCapacity * 7/10); itr++){
                try {
                    parkCar();
                    sleep(500);
                } catch (InterruptedException e) {
                    System.out.println(format("parkCar() {0} thread interrupted.", threadName));
                    e.printStackTrace();
                }
            }
    
            // sleep for a second and let the unloaded cars from ferry enter the lot
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                System.out.println(format("sleep() {0} thread interrupted while idle time.", threadName));
                e.printStackTrace();
            }
            // remove some cars
            for(int itr = 0; itr < ThreadLocalRandom.current().nextInt(SemaphoreDriver.parkingCapacity * 5/10); itr++){
                try {
                    removeCar();
                    sleep(500);
                } catch (InterruptedException e) {
                    System.out.println(format("removeCar() {0} thread interrupted.", threadName));
                    e.printStackTrace();
                }
            }
            
        }

    }
    
    void parkCar(){
        try {
            System.out.println(format("Parking the car. {0} is waiting for entry permit.", threadName));
            parkingSemaphore.acquire();
            System.out.println(format("Parked the car. {0} acquired permit. Current cars on the lot: {1}",
                    threadName, SemaphoreDriver.parkingCapacity - parkingSemaphore.availablePermits()));
        } catch (InterruptedException e) {
            System.out.println(format("parkCar() {0} thread interrupted.", threadName));
            e.printStackTrace();
        }
    }
    
    void removeCar(){
        System.out.println(format("{0} releasing the permit. Current cars on the lot: {1}",
                threadName, SemaphoreDriver.parkingCapacity - parkingSemaphore.availablePermits()));
        parkingSemaphore.release();
        parkingSemaphore.notify();
    }
}
