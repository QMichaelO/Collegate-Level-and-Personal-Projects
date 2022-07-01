
public class Patient extends Person{
    String condition;
    int vitals;
    public Patient(String occupation) {
        super(occupation);
    }
    public void setCondition(String condition){
        this.condition = condition;
    }
}
