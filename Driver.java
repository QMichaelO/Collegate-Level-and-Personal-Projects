
public class Driver {
        public static void main(String[] args) {
            Person dave = new Person("retired");
            Receptionist diane = new Receptionist("receptionist");
            Nurse emily = new Nurse("nurse");
            Doctor dan = new Doctor("doctor");
            Surgeon sam = new Surgeon("surgeon");
            Administrator amy = new Administrator("administrator");
            Janitor jim = new Janitor("janitor");
            
            System.out.println("A Brave New Telenovela: \n\tFeaturing: \n\n\tPerson\n\tReceptionist\n\tNurse\n\tDoctor\n\tSurgeon\n\tAdministrator\n\tJanitor Jim\n ");
            dave.work(" My toe hurts");
            diane.work();
            dave.work(dave.aliment);
            sam.setPatient(dan.setPatient(emily.setPatient(diane.setPatient(dave))));
            emily.checkVitals(0);
            dan.diagnosis(emily.patient.condition);
            sam.work();
            amy.work();
            amy.firePeople(sam);
            jim.work(emily.patient.condition);
            System.out.println("FIN");
    }
}
