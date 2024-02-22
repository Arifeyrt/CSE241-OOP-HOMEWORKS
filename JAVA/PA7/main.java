public class main {

    public static void main(String[] args) {

        Dataset ds = new Dataset();
        // creates an instance of the Dataset class.
        Player p1 = new Player();
        Player p2 = new Player();
        Viewer v1 = new Viewer();
        Viewer v2 = new Viewer();

        // create instances of the Player and Viewer classes.
        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        ds.register(v2);

        // register the Player and Viewer objects with the Dataset object.
        ds.add(new Image("imagename1", "dimension info1", "other info1"));
        ds.add(new Image("imagename2", "dimension info2", "other info2"));
        ds.add(new Image("imagename3", "dimension info3", "other info3"));
        ds.add(new Image("imagename4", "dimension info4", "other info4"));
        ds.add(new Image("imagename5", "dimension info5", "other info5"));
        ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));
        ds.add(new Video("videoname1", "duration1", "other info1"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Video("videoname3", "duration3", "other info3"));
        ds.add(new Text("textname1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

        Text Text4 = new Text("text4", "info4");
        ds.add(Text4);

        System.out.println("Viewer 1:");
        v1.show_list();
        System.out.println();

        System.out.println("Player 1:");
        p1.show_list();
        System.out.println();

        System.out.println("************REMOVE*******************");
        ds.remove(Text4);
        System.out.println("Viewer 1 after removing a text4:");
        System.out.println();
        System.out.println("current list:");
        v1.show_list();

        System.out.println("************REMOVE*******************");
        Playable po = p1.currently_playing();
        System.out.println("p1 currently playing this:");
        // This prints info about the playing object.
        po.info();
        System.out.println();
        ds.remove((Baseclass) po);
        System.out.println("current list:");
        p1.show_list();
        System.out.println();

        System.out.println("***************NEXT-PREVIOUS****************");
        System.out.println("Currently playing Viewer object: ");
        NonPlayable np = v1.currently_viewing();
        np.info();
        System.out.println();

        System.out.println("************NEXT************:");
        v1.next("image");
        System.out.println("v1 after next viewing this:");
        v1.currently_viewing().info();
        System.out.println();

        v1.next("image");
        System.out.println("v1 after next viewing this:");
        v1.currently_viewing().info();
        System.out.println();

        v1.next("image");
        System.out.println("v1 after next viewing this:");
        v1.currently_viewing().info();
        System.out.println();

        v1.next("image");
        System.out.println("v1 after next viewing this:");
        v1.currently_viewing().info();
        System.out.println();

        v1.next("text");
        System.out.println("v1 after next viewing this:");
        v1.currently_viewing().info();
        System.out.println();

        System.out.println("************PREVIOUS************:");
        v1.previous("image");
        System.out.println("v1 after previous viewing this:");
        v1.currently_viewing().info();
        System.out.println();
        System.out.println();

        System.out.println("************************************************");
        System.out.println("Currently playing player object: ");
        Playable p = p1.currently_playing();
        p.info();
        System.out.println();

        System.out.println("************NEXT************:");
        p1.next("audio");
        System.out.println("v1 after next viewing this:");
        p1.currently_playing().info();
        System.out.println();

        p1.next("video");
        System.out.println("v1 after next viewing this:");
        p1.currently_playing().info();
        System.out.println();

        p1.next("video");
        System.out.println("v1 after next viewing this:");
        p1.currently_playing().info();
        System.out.println();

        System.out.println("************PREVIOUS************:");
        p1.previous("video");
        System.out.println("v1 after previous viewing this:");
        p1.currently_playing().info();
        System.out.println();

        System.out.println("************NEXT************:");
        p1.next("video");
        System.out.println("v1 after next viewing this:");
        p1.currently_playing().info();
        System.out.println();

        System.out.println("************NEXT************:");
        p1.next("video");
        System.out.println("v1 after next viewing this:");
        p1.currently_playing().info();
        System.out.println();

    }
}