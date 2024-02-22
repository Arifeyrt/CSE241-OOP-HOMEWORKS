import java.util.ArrayList;

public class Player implements Observer {
    // player entry objects stores here
    private ArrayList<Playable> data;
    // we have an index for finding next and previous infos
    private int index;

    // constructor
    public Player() {
        index = 0;
        data = new ArrayList<Playable>();
    }

    // showlist
    public void show_list() {
        for (Playable p : data) {
            p.info();
        }
    }

    // skips next data
    public void next(String type) {
        if (type == "video") {// video
            for (int i = index + 1; i < data.size(); i++) {// we start from the next index
                if (data.get(i) instanceof Video) {
                    index = i;
                    return;
                }
            }
        }
        if (type == "audio") {// if audio
            for (int i = index + 1; i < data.size(); i++) {
                if (data.get(i) instanceof Audio) {
                    index = i;
                    return;
                }
            }
        }

    }

    // skips previous data
    public void previous(String type) {

        if (type == "video") {
            for (int i = index - 1; i >= 0; i--) {// we start from the previous index
                if (data.get(i) instanceof Video) {
                    index = i;
                    return;
                }
            }
        }
        if (type == "audio") {
            for (int i = index - 1; i >= 0; i--) {// we start from the previous index
                if (data.get(i) instanceof Audio) {
                    index = i;
                    return;
                }
            }
        }
    }

    // shows currently playing data
    public Playable currently_playing() {
        return (Playable) data.get(index);
    }

    // we find playable datas from all entries and store
    @Override
    public void update(Baseclass entries) {

        if (data.contains(entries)) {
            data.remove((Playable) entries);
        } else {
            data.add((Playable) entries);
        }

    }
}