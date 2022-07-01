
public class Receptionist extends Person{
    Patient patient;
    public Receptionist(String occupation) {
        super(occupation);
    }
    public void work(){
        System.out.println("Receptionist: If you could give us your age, Date of Birth, and what currently seems to be the problem \n");
    }
    public Patient setPatient(Person patient){
        this.patient = new Patient(patient.getOccupation());
        this.patient.setCondition(patient.getAliment());
        System.out.println("Receptionist: Thank you for all of your information, if you could just wait for a brief moment the nurse will be right with you \n");
        return this.patient;
    }
    public Patient getPatient(){
        return patient;
    }
}
