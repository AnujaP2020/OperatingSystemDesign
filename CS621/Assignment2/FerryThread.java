import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

import static java.text.MessageFormat.format;

/**
 * @author anuja
 * @netId: yd1530
 * @created 2/21/21
 */

public class FerryThread extends Thread {
    Semaphore parkingSemaphore;
    String threadName;
    int carsOnTheFerry = 0;
    
    public FerryThread(Semaphore parkingSemaphore, String threadName){
        super(threadName);
        this.threadName = threadName;
        this.parkingSemaphore = parkingSemaphore;
    }
    
    @Override
    public void run(){
        // uncomment this to run for more than 1 time
        // for(int runner = 0; runner < ThreadLocalRandom.current().nextInt(5); runner++){
        
        for(int runner = 0; runner < 1; runner++){
            // load cars as long as parking spots are available and ferry capacity is not reached
            while((parkingSemaphore.availablePermits() > 0) && (carsOnTheFerry < SemaphoreDriver.ferryCapacity)){
                loadCar();
                try {
                    sleep(500);
                } catch (InterruptedException e) {
                    System.out.println(format("sleep() {0} thread interrupted while loading the car.", threadName));
                    e.printStackTrace();
                }
            }
    
            // travel: add sleep()
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                System.out.println(format("sleep() {0} thread interrupted while traveling.", threadName));
                e.printStackTrace();
            }
    
            // unload cars
            for(int itr = 0; itr < carsOnTheFerry; itr++){
                unloadCar();
                try {
                    sleep(500);
                } catch (InterruptedException e) {
                    System.out.println(format("sleep() {0} thread interrupted while unloadCar().", threadName));
                    e.printStackTrace();
                }
            }
    
            // load cars from parking lot: add sleep()
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                System.out.println(format("sleep() {0} thread interrupted when waiting before " +
                                                  "loadCarFromParkingLot().", threadName));
                e.printStackTrace();
            }
    
            // start loading cars from parking lot.
            // This should be minimum of ferry capacity or number of cars parked on the parking lot
            for(int itr = 0; itr < Math.min(SemaphoreDriver.ferryCapacity,
                    (SemaphoreDriver.parkingCapacity - parkingSemaphore.availablePermits())); itr++){
                loadCarFromParkingLot();
                try {
                    sleep(500);
                } catch (InterruptedException e) {
                    System.out.println(format("sleep() {0} thread interrupted while loadCarFromParkingLot()", threadName));
                    e.printStackTrace();
                }
            }
        }
    }
    
    // load car from the mainland to go to island parking lot.
    // We acquire semaphore in this case (reserve a parking spot on the island parking lot)
    void loadCar(){
        try {
            System.out.println(format("{0} is checking parking availability to load a car.", threadName));
            parkingSemaphore.acquire();
            carsOnTheFerry++;
            System.out.println(format("Parking permit secured. {0} loaded the car. Available parking: {1}. " +
                                              "Current cars on the ferry {2}.",
                    threadName,
                    SemaphoreDriver.parkingCapacity - parkingSemaphore.availablePermits(),
                    carsOnTheFerry));
        } catch (InterruptedException e) {
            System.out.println(format("loadCar() {0} thread interrupted while securing parking permit.", threadName));
            e.printStackTrace();
        }
    }
    
    // load car from the island to go to the mainland.
    // We release semaphore in this case (remove the car from island parking lot)
    void loadCarFromParkingLot(){
        System.out.println(format("{0} removing car from the parking lot and loading on the ferry.", threadName));
        parkingSemaphore.release();
        parkingSemaphore.notify();
        carsOnTheFerry++;
        System.out.println(format("{0} current cars on the ferry {1}", threadName, carsOnTheFerry));
    }
    
    void unloadCar(){
        System.out.println(format("{0} unloading cars from the ferry to the parking lot. Current cars on the " +
                                          "ferry {1}", threadName, carsOnTheFerry));
        carsOnTheFerry--;
    }
    
}
