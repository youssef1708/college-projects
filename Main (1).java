/////// OS Assignment 3 //////
import java.util.*;
//////////////////// class partition ////////////////////////
class partition{
    String partition_name;   // String to save partition name
    int  capacity;         // Int to store the entered capacity
    int remaining_capacity;     // int to store updated capacity after the process input
    Boolean is_empty = false; //
    String occupying_process;

    public void set_partition_attributes(String partition_name, int capacity)      // Constructor
    {
        this.partition_name = partition_name;
        this.capacity = capacity;
        remaining_capacity = capacity;
        occupying_process = "External fragment ";
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public void setRemaining_capacity(int remaining_capacity) {
        this.remaining_capacity = remaining_capacity;
    }

    public void setPartition_name(String partition_name) {
        this.partition_name = partition_name;
    }

    public String getOccupying_process() {
        return occupying_process;
    }

    public void setOccupying_process(String occupying_process) {
        this.occupying_process = occupying_process;
    }

    public int getRemaining_capacity() {
        return remaining_capacity;
    }

    public String getPartition_name() {
        return partition_name;
    }

    public int getCapacity() {
        return capacity;
    }

    public Boolean getIs_empty() {
        return is_empty;
    }

    public void setIs_empty(Boolean is_empty) {
        this.is_empty = is_empty;
    }

    public void print_attributes()
    {
        System.out.println("name: " + partition_name +" (" +capacity+"kb) " + "=> " + occupying_process);

    }
}

//////////////////// class process  ////////////////////////
class process{
    String process_name;                         // String to save process name
    String partition_name;                      // String to store the partition name which process entered
    int process_space;                            // Int to save space of process

    public void set_process_attributes(String process_name, int process_space)           // constructor
    {
        this.process_name = process_name;
        this.process_space = process_space;
        partition_name="This process didn't added to a partition yet";

    }

    public void setPartition_name(String partition_name) {
        this.partition_name = partition_name;
    }

    public String getProcess_name() {
        return process_name;
    }

    public int getProcess_space() {
        return process_space;
    }

    public String getPartition_name() {
        return partition_name;
    }
}

class compaction{
    int partitions; // Int to hold the number of partitions
    ArrayList<partition> part_array; // ArrayList of type partition to hold the partitions
    process[] proc_array;  // Array of type process to hold the process

    // Class constructor
    public compaction(ArrayList<partition> part_array, process[] proc_array,int partitions ){
        this.partitions = partitions;
        this.part_array = (ArrayList<partition>) part_array.clone();
        this.proc_array = proc_array.clone();
    }

    public void apply_compaction()
    {
        int choice;
        boolean is_choice_valid = false;

        // While loop for input validation
        while (!is_choice_valid){

            System.out.println("Do you want to compact?");
            System.out.println("1-yes");
            System.out.println("2-No");

            Scanner scn = new Scanner(System.in);
            choice = scn.nextInt();

            if (choice == 1)
            {
                is_choice_valid = true;

                int total_external_size = 0;
                int size=part_array.size();

                // For loop to remove the external fragments, and store the total capacity in an int
                for (int i = 0; i < size; i++)
                {
                    // Checking if the external fragments does not contain any processes
                    if (part_array.get(i).getRemaining_capacity() == part_array.get(i).getCapacity()) {
                        total_external_size += part_array.get(i).getRemaining_capacity();
                        part_array.set(i, null);
                    }

                }
                // Creating a new partition with all the external fragments and adding it to the partition array
                partitions++;
                String part_name = "partition" + partitions;
                partition new_partition = new partition();
                new_partition.set_partition_attributes(part_name, total_external_size);
                part_array.add(new_partition);

                System.out.println("After compact");
                for (process process : proc_array) { // Iterating the process array

                    if (Objects.equals(process.getPartition_name(), "can not be allocated")) {

                        // If the non-allocated process is smaller than the new partition
                        if (process.getProcess_space() <= new_partition.getRemaining_capacity()) {

                            process.setPartition_name(new_partition.getPartition_name()); // Setting the process's partition name to the new partition
                            new_partition.setOccupying_process(process.getProcess_name());// adding the process's name to the partition

                            int remain_cap = new_partition.getRemaining_capacity() - process.getProcess_space(); // Checking if there is an additional capacity left in the partition
                            new_partition.setRemaining_capacity(0);
                            new_partition.setCapacity(process.getProcess_space()); // Making the partition's capacity equal to the process space

                            // If the partition has more capacity than the process space
                            if (remain_cap > 0) {
                                // Create a new partition with the remaining space
                                partition part = new partition();
                                partitions ++;
                                String partName = "partition " + partitions;
                                part.set_partition_attributes(partName, remain_cap);
                                part_array.add(part);
                            }
                        }
                    }
                }
                // Printing the partitions after compaction
                for (partition partition : part_array) {
                    if (partition != null) {
                        partition.print_attributes();
                    }
                }

            } else if (choice == 2) {
                is_choice_valid = true;
                System.out.println("Thank You");


            } else {
                System.out.println("Wrong input please try again");
            }
        }

    }
}

class Best_Fit {
    ArrayList<partition> part_array = new ArrayList<partition>();
    process[] proc_array;
    int partitions;

    // Class constructor
    public Best_Fit(ArrayList<partition> part_array, process[] processes_array)
    {
        this.proc_array = processes_array.clone();
        this.partitions = part_array.size()-1;
        this.part_array=  (ArrayList<partition>) part_array.clone();

    }

    public void best_fit() {
        for (int i = 0; i < proc_array.length; i++)
        {
            int bestPartition = the_best_fit(proc_array[i], part_array); // Index of partition using best-fit policy

            if (bestPartition != -1)// If a suitable partition was found
            {
                int remaining_capacity = part_array.get(bestPartition).getRemaining_capacity() - proc_array[i].getProcess_space();

                // Setting the capacity of best fit partition to size of the entering process
                // and set its rem time to 0
                part_array.get(bestPartition).setCapacity(proc_array[i].getProcess_space());
                part_array.get(bestPartition).setRemaining_capacity(0);

                // Setting the process partition name with the partition name it's allocated to
                proc_array[i].setPartition_name(part_array.get(bestPartition).getPartition_name());
                part_array.get(bestPartition).setOccupying_process(proc_array[i].getProcess_name());

                // Creating a new partition with the remaining space as its capacity
                // and name of the last partition created + 1
                if (remaining_capacity!=0)
                {
                    partitions ++;
                    String part_name = "partition" + partitions;
                    partition new_partition = new partition();
                    new_partition.set_partition_attributes(part_name, remaining_capacity);
                    // add it to the partitions array list after the previous partition
                    part_array.add(bestPartition + 1,new_partition); //bestPartition + 1
                }
            }
            else // No partition is suitable
            {
                proc_array[i].setPartition_name("can not be allocated");
                System.out.println(proc_array[i].getProcess_name()+" can not be allocated");
            }


        }

        // Printing the partitions' attributes
        for (partition partition : part_array) {
            partition.print_attributes();
        }

        // Creating an object of type compaction
        compaction com = new compaction(part_array, proc_array,par/titions);
        com.apply_compaction();

    }

    // This function returns the best suitable partition for a process.
    public int the_best_fit(process proc, ArrayList<partition> partitionArrayList) {
        int min =Integer.MAX_VALUE;
        int min_ind = -1;

        // Iterating the partitions array and finding the most suitable fit for a process
        for (int i = 0; i < partitionArrayList.size(); i++) {
            int difference =partitionArrayList.get(i).getCapacity()-proc.getProcess_space();

            // If the remaining capacity is greater than the size of process and less than the minimum (the remaining capacity after insertion is less)
            if ((partitionArrayList.get(i).getRemaining_capacity() >= proc.getProcess_space()) && (difference< min)) {
                min = difference;
                min_ind = i;
            }

        }
        return min_ind;
    }

}


class First_fit {

    ArrayList<partition> part_array = new ArrayList<partition>();
    process[] proc_array;
    int partitions;


    public First_fit(ArrayList<partition> part_array, process[] processes_array)
    {
        this.proc_array = processes_array.clone();
        this.partitions = part_array.size()-1;
        this.part_array=  (ArrayList<partition>) part_array.clone();

    }

    public void Firstfit(){

        // Location array is used to tell if a process has a partition
        int[] location= new int[proc_array.length];
        // for each process[i] have initial partition number -1
        for (int i = 0; i < proc_array.length; i++) {
            location[i]=-1;
        }

        // Getting the first fit
        // i loops on the number of processes
        for (int i = 0; i <proc_array.length; i++) {
            // j loops on number of partitions
            for (int j = 0; j < part_array.size(); j++) {
                // Checking if the burst time less than the partition capacity
                // and also empty where no process in that partition
                if(proc_array[i].process_space<=part_array.get(j).remaining_capacity && part_array.get(j).is_empty==false) {
                    part_array.get(j).setOccupying_process(proc_array[i].getProcess_name());
                    part_array.get(j).setIs_empty(true);
                    // getting the remaining capacity
                    int rem = part_array.get(j).remaining_capacity-proc_array[i].process_space;
                    // where location process[i] at partiton j
                    location[i]=j;
                    // if there is a remainder then we add a new partition
                    if(rem!=0)
                    {
                        partition z= new partition();
                        partitions++;
                        String f="Partition"+ partitions;
                        z.set_partition_attributes(f,rem);
                        part_array.add(j+1,z);
                    }
                    // setting the partition's capacity with the process size
                    part_array.get(j).setCapacity(proc_array[i].process_space);
                    break;
                }

            }

        }
        // Printing the Partitions
        for (int i = 0; i < part_array.size(); i++) {
            part_array.get(i).print_attributes();

        }

        // Printing the [not be allocated] Processes
        for (int i = 0; i < proc_array.length; i++) {
            {
                if(location[i]==-1){
                    proc_array[i].setPartition_name("can not be allocated");
                    System.out.println(proc_array[i].getProcess_name()+" can not be allocated");
                }

            }
        }

        // Calling Compaction
        compaction com = new compaction(part_array, proc_array,partitions);
        com.apply_compaction();


    }

}


class Worst_fit{
    ArrayList<partition> part_array = new ArrayList<partition>();
    process[] proc_array;
    int partitions;


    public Worst_fit(ArrayList<partition> part_array, process[] processes_array)
    {
        this.proc_array = processes_array.clone();
        this.partitions = part_array.size()-1;
        this.part_array= (ArrayList<partition>) part_array.clone();

    }

    public void worst_fit() {
        for (int i = 0; i < proc_array.length; i++)
        {
            int worst_partition = the_worst_fit(proc_array[i], part_array); // Index of partition using worst-fit policy

            if (worst_partition != -1)// If a suitable partition was found
            {
                int remaining_capacity = part_array.get(worst_partition).getRemaining_capacity() - proc_array[i].getProcess_space();

                // Setting the capacity of worst fit partition to size of the entering process
                // and set its rem time to 0
                part_array.get(worst_partition).setCapacity(proc_array[i].getProcess_space());
                part_array.get(worst_partition).setRemaining_capacity(0);

                // Setting the process partition name with the partition name it's allocated to
                proc_array[i].setPartition_name(part_array.get(worst_partition).getPartition_name());
                part_array.get(worst_partition).setOccupying_process(proc_array[i].getProcess_name());

                // Creating a new partition with the remaining space as its capacity
                // and name of the last partition created + 1
                if (remaining_capacity!=0)
                {
                    partitions += 1;
                    String part_name = "partition" + partitions;
                    partition new_partition = new partition();
                    new_partition.set_partition_attributes(part_name, remaining_capacity);
                    // add it to the partitions array list after the previous partition
                    part_array.add(worst_partition + 1,new_partition);//worstPartition + 1
                }
            }
            else // No partition is suitable
            {
                proc_array[i].setPartition_name("can not be allocated");
                System.out.println(proc_array[i].getProcess_name()+" can not be allocated");
            }

        }

        // Printing the partitions' attributes
        for (partition partition : part_array) {
            partition.print_attributes();
        }

        // Creating an object of type compaction
        compaction com = new compaction(part_array, proc_array,partitions);
        com.apply_compaction();

    }
    ///this function returns the best suitable partition for a process.
    public int the_worst_fit(process proc, ArrayList<partition> partitionArrayList) {
        int max =Integer.MIN_VALUE;
        int max_index = -1;

        // Iterating the partitions array and finding the most suitable fit for a process
        for (int i = 0; i < partitionArrayList.size(); i++) {
            int difference = partitionArrayList.get(i).getCapacity() - proc.getProcess_space();

            // If the remaining capacity of the partition is greater than the size of process and more than the max (the remaining capacity after insertion is more)
            if ((partitionArrayList.get(i).getRemaining_capacity() >= proc.getProcess_space()) && (difference > max)) {
                max = difference;
                max_index = i;
            }
        }
        return max_index;
    }

}
public class Main
{
    public static void main(String[] args)
    {
        Scanner scn = new Scanner(System.in);

        System.out.print("Enter number of partitions: ");

        int num = scn.nextInt();
        ArrayList<partition> arr_f = new ArrayList<>();
        ArrayList<partition> arr_b = new ArrayList<>();
        ArrayList<partition> arr_w = new ArrayList<>();



        int capacity;
        String partition_name;

        for (int i = 0; i < num; i++)  // For loop to get each partition capacity
        {
            int print= i + 1;

            System.out.print("please enter the name of partition number " + print + ":");
            partition_name=scn.next();

            System.out.print("please enter the size of " + partition_name + ":");
            capacity=scn.nextInt();

            partition temp_f = new partition();
            temp_f.set_partition_attributes(partition_name,capacity);
            partition temp_w = new partition();
            temp_w.set_partition_attributes(partition_name,capacity);
            partition temp_b = new partition();
            temp_b.set_partition_attributes(partition_name,capacity);

            temp_f.is_empty=false;
            temp_w.is_empty=false;
            temp_b.is_empty=false;

            arr_b.add(temp_b);
            arr_w.add(temp_w);
            arr_f.add(temp_f);

        }

        System.out.print("Enter number of processes : ");
        int num_of_processes = scn.nextInt();

        process[] processes_array = new process[num_of_processes];         // array of processes with size of entered value
        for (int i = 0; i < num_of_processes; i++) {
            processes_array[i] = new process();
        }

        int process_space;
        String process_name;

        for (int i = 0; i < num_of_processes; i++)                        // for loop to get each process space
        {
            int print= i + 1;
            System.out.print("please enter the name of process number "+print+":");
            process_name=scn.next();

            System.out.print("please enter the burst time of "+process_name+":");
            process_space=scn.nextInt();

            processes_array[i].set_process_attributes(process_name,process_space);
        }

        int selector;
        while (true)
        {
            System.out.println("Enter your choice:");
            System.out.println("1-First Fit");
            System.out.println("2-Best Fit");
            System.out.println("3-Worst Fit");
            System.out.println("4-EXIT");

            System.out.println("-----------------------------------------------------");
            System.out.print("Choice:");

            selector=scn.nextInt();

            switch (selector){
                case 1: {
                    First_fit first_fit = new First_fit(arr_f, processes_array);
                    first_fit.Firstfit();
                    continue;
                }
                case 2: {
                    Best_Fit best_fit = new Best_Fit(arr_b,processes_array);
                    best_fit.best_fit();
                    continue;
                }
                case 3: {
                    Worst_fit worst_fit = new Worst_fit(arr_w,processes_array);
                    worst_fit.worst_fit();
                    continue;
                }

                case 4: {
                    System.out.println("Thank you");
                    return;

                }

                default:
                {
                    System.out.println("Please enter a correct choice.");
                }
            }
        }

    }
}