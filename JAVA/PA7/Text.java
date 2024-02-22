class Text extends Baseclass implements NonVisual, NonPlayable {
    private String content;

    // cpnstructer
    public Text(String name, String content_) {
        super(name);
        content = content_;
    }

    // set content
    public void set_content(String content_) {
        content = content_;
    }

    // get content
    public String get_content() {
        return content;
    }

    // print info
    public void info() {
        System.out.println("text: " + get_name());
        System.out.println("content: " + get_content());
    }
}