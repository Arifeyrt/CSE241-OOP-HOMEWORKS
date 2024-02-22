class Audio extends Baseclass implements NonVisual, Playable {
    private String duration,other;
    
    //constructer
    public Audio(String name, String duration_,String other_) {
        super(name);
        duration = duration_;
        other=other_;
    }
    //set duration
    public void set_duration(String duration_){
        duration=duration_;
    }
    //get duration
    public String get_duration(){
        return duration;
    }
 
    //print info
    public void info()
    {
        System.out.println("audio: " + get_name());
        System.out.println("duration: " + get_duration());
    }
}