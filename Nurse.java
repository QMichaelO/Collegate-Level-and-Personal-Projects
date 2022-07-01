public class Nurse extends Receptionist{
    
    public Nurse(String occupation) {
        super(occupation);
    }
    
    @Override public void work(){
        System.out.println("Nurse: If you could come right this way. I just need to check you vitals real quick and the doctor will be right with you. \n");
    }
    public int checkVitals(int vitals){
        patient.vitals = vitals;
        System.out.println("Nurse: Oh my! Your vitals are " + vitals + " we need to get the doctor immediately \n");
        return vitals;
    }
    public Patient setPatient(Patient patient){
        this.patient = patient; 
        return patient;
    }
    
}
