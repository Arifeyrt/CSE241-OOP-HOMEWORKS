import java.util.ArrayList;

public class Viewer implements Observer {

    private ArrayList<NonPlayable> data;

    private int index;

    // constructor
    public Viewer() {
        index = 0;
        data = new ArrayList<NonPlayable>();
    }

    public void show_list() {
        for (NonPlayable p : data) {
            p.info();
        }
    }

    // skips next data
    public void next(String type) {
        if (type == "image") {
            for (int i = index + 1; i < data.size(); i++) {
                if (data.get(i) instanceof Image) {
                    index = i;
                    return;
                }
            }
        }
        if (type == "text") {
            for (int i = index + 1; i < data.size(); i++) {
                if (data.get(i) instanceof Text) {
                    index = i;
                    return;
                }
            }
        }

    }

    // skips previous data
    public void previous(String type) {
        {
            if (type == "image") {
                for (int i = index - 1; i >= 0; i--) {
                    if (data.get(i) instanceof Image) {
                        index = i;
                        return;
                    }
                }
            }
            if (type == "text") {
                for (int i = index + 1; i >= 0; i--) {
                    if (data.get(i) instanceof Text) {
                        index = i;
                        return;
                    }
                }
            }

        }
    }

    // shows currently playing data
    public NonPlayable currently_viewing() {
        return (NonPlayable) data.get(index);
    }

    // we find playable datas from all entries and store
    @Override
    public void update(Baseclass entries) {

        if (data.contains(entries)) {
            data.remove((NonPlayable) entries);
        } else {
            data.add((NonPlayable) entries);
        }

    }
}