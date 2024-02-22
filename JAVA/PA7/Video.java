class Video extends Baseclass implements Visual, Playable {
    private String duration, other;

    // constructer
    public Video(String name, String duration, String other) {
        super(name);
        this.duration = duration;
        this.other = other;
    }

    // Set
    public void set_dimension(String duration_) {
        duration = duration_;
    }

    // get set
    public String get_duration() {
        return duration;
    }


    //print
    public void info() {
        System.out.println("video: " + get_name());
        System.out.println("duration: " + get_duration());
    }
}