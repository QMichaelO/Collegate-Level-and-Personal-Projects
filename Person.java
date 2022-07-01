
public class Person {
    String occupation;
    String aliment;
    
    public Person(String occupation){
        this.occupation = occupation;
    }
    public String work(String comment){
        aliment = comment;
        System.out.println("Person:" + comment + "\n");
        return comment;
    }
    public String getOccupation(){
        return occupation;
    }
    public String getAliment(){
        return aliment;
    }
}
