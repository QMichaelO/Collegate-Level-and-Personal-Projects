
public class Administrator extends Person{
    
    public Administrator(String occupation) {
        super(occupation);
    }
    
    public void work(){
        System.out.println("Administrator: Carl how do you mess up this badly!\n");
    }

    public void firePeople(Person person) {
        System.out.println("Administator: You're fired!\n ");
        person.occupation = "Unemployeed";
    }
}
