
public class Surgeon extends Nurse{
    
    public Surgeon(String occupation) {
        super(occupation);
    }
    
    @Override public void work(){
        System.out.println("Surgeon: Don't worry we have been preparing for most of the day for this moment, we will take care of you and make sure that everything goes smoothily\n");
        System.out.println("*it was at this moment the patient faints and is unconcious*\n");
        playMusic();
        performSurgery();
    }
    public void playMusic(){
        System.out.println("Surgeon: Alexa play Despacito\n ");
        System.out.println("Alexa: Playing your *try not to mess up playlist* \n");
    }

    private void performSurgery() {
        System.out.println("Surgeon: Oops\n");
        System.out.println("*it was at this moment the surgeon's scalpel slipped and lacerated the aortic valve and the patient passes mere moments later* \n");
        patient.occupation = "dead";
    }
}
