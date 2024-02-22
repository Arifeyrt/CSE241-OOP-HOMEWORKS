
import java.util.ArrayList;

class Dataset {
    private ArrayList<Baseclass> objects;
    private ArrayList<Observer> observers;

    // constructer
    public Dataset() {
        objects = new ArrayList<>();
        observers = new ArrayList<>();
    }

    // constructer
    public Dataset(ArrayList<Baseclass> Data) { // create arraylists with data
        observers = new ArrayList<Observer>();
        objects = Data;
    }

    // add function
    public void add(Baseclass object) {
        objects.add(object);
        notifyObservers(object);
    }

    // remove function
    public void remove(Baseclass object) {
        objects.remove(object);
        notifyObservers(object);
    }

    // register
    public void register(Observer new_obser) {
        observers.add(new_obser);

    }

    // we remove an observer and give deleted message
    public void unregister(Observer remove_observer) {
        int index_observer = observers.indexOf(remove_observer);
        System.out.println("\nObserver " + (index_observer + 1) + " removed\n");
        observers.remove(index_observer);
    }

    // we have to notify observers from updates
    public void notifyObservers(Baseclass object) {
        for (Observer observer : observers) {
            if (object instanceof Playable && observer instanceof Player)
                observer.update(object);
            if (object instanceof NonPlayable && observer instanceof Viewer)
                observer.update(object);
        }
    }

}