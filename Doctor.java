/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Quintin
 */
public class Doctor extends Nurse{
    
    public Doctor(String occupation) {
        super(occupation);
    }
    @Override public void work(){
        System.out.println("Doctor: Nurse what seems to be the problem!\n");
        diagnosis(patient.condition);
    }
    public void diagnosis(String condition){
        System.out.println("Doctor: Oh my the patient said they were struggling with " + condition + " and their vitals were " + patient.vitals +"\n");
        System.out.println("Doctor: That is indicative of kidney faliure. Luckily we foresaw this and have your brother Julio on standby ready and prepared for the procedure. \n");
    }
}
