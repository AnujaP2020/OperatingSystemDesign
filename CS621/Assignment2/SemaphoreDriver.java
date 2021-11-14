import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;

/**
 * @author anuja
 * @netId: yd1530
 * @created 2/21/21
 */

/*
    ** Logic **
    
*    parkingSemaphore: this is used as semaphore to control the number of parking spots available and notify other thread
    when there a spot becomes available or a car is available to be picked up be the ferry.

*     SemaphoreDriver.java:
    * Creates and starts both the ferry and parking threads

*     ParkingThread,java:
    * This handles parking and removing car from the parking lot
    * parkCar(): blocks a parking spot by acquiring the semaphore lock
    * removeCar(): frees up a parking spot by releasing the semaphore lock and notifies the ferry thread that a parking
    spot has become available and car will be waiting to be picked up

*    FerryThread.java:
    * handles loading and unloading of the cars on the ferry.
    * while loading the car (loadCar()), it checks the available parking spots and only loads the car if the parking
    spot is available.
    * loadCarFromParkingLot(): the is when we load the cars into the Ferry from the parking lot and notify of available
    parking lots
*/


public class SemaphoreDriver {
    
    static int ferryCapacity = 50, parkingCapacity = 100, totalCars = 150;
    
    public static void main(String[] args){
        
        System.out.println("Starting semaphore driver.");
        Semaphore parkingSemaphore  = new Semaphore(parkingCapacity);
        List<Thread> ferryThreadList = new LinkedList<>();
        List<Thread> parkingThreadList = new LinkedList<>();
        
        for(int itr = 0; itr < 5; itr++){
            Thread ferryThread = new FerryThread(parkingSemaphore, "ferryThread-" + itr);
            Thread parkingThread = new ParkingThread(parkingSemaphore, "parkingThread-" + itr);
            
            ferryThreadList.add(ferryThread);
            parkingThreadList.add(parkingThread);
        }
        
        for(Thread ferryThread : ferryThreadList){
            ferryThread.start();
        }
        for(Thread parkingThread : parkingThreadList){
            parkingThread.start();
        }
    
        try {
            for(Thread ferryThread : ferryThreadList){
                ferryThread.join();
            }
            for(Thread parkingThread : parkingThreadList){
                parkingThread.join();
            }
        } catch (InterruptedException e) {
            System.out.println("Error waiting for the threads to finish.");
            e.printStackTrace();
        }
        
        System.out.println("Exiting semaphore driver.");
    }
}
