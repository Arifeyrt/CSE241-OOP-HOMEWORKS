class Image extends Baseclass implements Visual, NonPlayable {
    private String dimension, other;

    // constructer
    public Image(String name, String dimension, String other) {
        super(name);
        this.dimension = dimension;
        this.other = other;
    }

    // get dimension
    public String get_dimension() {
        return dimension;
    }

    // Set dimension
    public void set_dimension(String dimension_) {
        dimension = dimension_;
    }

    // print info
    public void info() {
        System.out.println("image: " + get_name());
        System.out.println("dimention: " + get_dimension());
    }
}