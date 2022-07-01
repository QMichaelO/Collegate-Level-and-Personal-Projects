
public class Janitor extends Person{
    
    public Janitor(String occupation) {
        super(occupation);
    }
    @Override public String work(String condition){
        System.out.println("Janitor Jim: Oh god not another one, that's the 5th one this week.\n ");
        System.out.println("Janitor Jim: Looks like this one died because " + condition);
        clean();
        return condition;
    }

    private void clean() {
        System.out.println("\n*Jim solmenly mops up all the blood off the floor*\n");
    }
}
