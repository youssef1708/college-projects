
import java.util.*;
import java.lang.Math;


class process{
    String process_name;
    int arrival_time, burst_time, priority, remaining_burst, waiting_time, finish_time, turnaround_time, ag_quantum;

    public void set_process_attributes(String process_name, int arrival_time, int burst_time, int priority,int ag_quantum)
    {
        this.process_name = process_name;
        this.arrival_time = arrival_time;
        this.burst_time = burst_time;
        this.priority = priority;
        this.ag_quantum = ag_quantum;
        remaining_burst = burst_time;
        finish_time = 0;
        waiting_time = 0;
        turnaround_time=0;
    }
    public void print_attributes(){
        System.out.println("name: " + process_name);
        System.out.println("arrival time: " + arrival_time);
        System.out.println("burst time: " + burst_time);
        System.out.println("priority: " + priority);
        System.out.println("waiting time: " + waiting_time);
        System.out.println("finish time " + finish_time);
        System.out.println("turnaround time: " + turnaround_time);
    }
    //////////////////////////////////// setters and getters ////////////////////////////////////////


    public int getAg_quantum() {
        return ag_quantum;
    }

    public int get_remaining_burst(){
        return remaining_burst;
    }

    public int get_arrival_time() {
        return arrival_time;
    }

    public int getBurst_time() {
        return burst_time;
    }

    public int getWaiting_time() {
        return waiting_time;
    }

    public int get_finish_time() {
        return finish_time;
    }

    public int get_turnaround_time() {
        return turnaround_time;
    }

    public int getPriority() {
        return priority;
    }

    public String getProcess_name() {
        return process_name;
    }

    public void setProcess_name(String process_name) {
        this.process_name = process_name;
    }

    public void setAg_quantum(int ag_quantum) {
        this.ag_quantum = ag_quantum;
    }

    public void setTurnaround_time(int turnaround_time) {
        this.turnaround_time = turnaround_time;
    }
    public void set_remaining_burst(int remaining_burst){
        this.remaining_burst = remaining_burst;
    }


    public void set_finish_time(int finish_time) {
        this.finish_time = finish_time;
    }

    public void setWaiting_time(int waiting_time) {
        this.waiting_time = waiting_time;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }
}


class AG_scheduling {
    // each process has a quantum.
    // at first: execute the process by 25% of its quantum (fcfs)
    // then: check priority, if it is the same process continue exec to 50%, if not update the 1st process quantum and put it in the queue then switch to the 2nd process. (priority)
    // exec the 2nd process by 25% then check the process with the lowest burst time (sjf), if it is the same process continue exec to 50% if not update the 1st process quantum and put it in the queue then switch to the 2nd process.
    // note: any process exec first by 25%
    // after sjf, check priority.......
    // then sjf.
    // if a process is finished then set its quantum to 0 and execute the first process in the queue

    public void ag_sch(process[] array){

        Queue<process> queue = new LinkedList<>();//  queue to put the processes in
        Queue<String> execution_order = new LinkedList<>(); // queue to hold the execution order to be printed

        int process_queue_count = 0;   //counter to count the number of processes added to the queue
        System.out.println("----------- AG SCHEDULING------------ ");

        process running_process ;
        int count=0; //counter to count number of processes finished to break

        mainloop:
        for (int time = 0; time < 999; time++) {

            if (process_queue_count < array.length) {
                if (array[process_queue_count].get_arrival_time() == time) {
                    queue.add(array[process_queue_count]);
                    process_queue_count++;
                }
            }

            System.out.print("quantum time for processes at time "+ time + ": ( " );
            for (process p : array){
                System.out.print(p.getAg_quantum() + ", ");
            }
            System.out.print(")");
            System.out.println();

            if (queue.isEmpty()) {
                continue  ;
            }

            running_process = queue.remove();
            execution_order.add(running_process.getProcess_name());

            outerloop:
            for (int elapsed_quantum = 0; elapsed_quantum < running_process.getAg_quantum();)
            {
                double quarter;
                quarter = 0.25 * running_process.getAg_quantum();
                int ceil25;
                ceil25 = (int) Math.ceil(quarter);
                int temp_remaining_burst = running_process.get_remaining_burst();
                int ag_quantum = running_process.getAg_quantum();

                for (int l = 0; l < ceil25; l++) {
                    running_process.set_remaining_burst(--temp_remaining_burst);
                    time++;
                    elapsed_quantum++;
                    if (process_queue_count < array.length) {
                        if (array[process_queue_count].get_arrival_time() == time) {
                            queue.add(array[process_queue_count]);
                            process_queue_count++;
                        }
                    }
                    if (running_process.get_remaining_burst() == 0) {
                        running_process.set_finish_time(time);
                        int turn_around;
                        running_process.setTurnaround_time(running_process.get_finish_time() - running_process.get_arrival_time());
                        turn_around = running_process.get_turnaround_time();
                        int process_time;
                        process_time = running_process.getBurst_time();
                        running_process.setWaiting_time(turn_around - process_time);
                        time--; // to make the next process start where the first process ended


                        running_process.setAg_quantum(0);
                        //updating the quantum time in the main process array
                        for (int i = 0; i < array.length; i++){
                            if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                                array[i].setAg_quantum(0);
                            }
                        }


                        // Logging the info into the array
                        for (int i = 0; i < array.length; i++) {
                            if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                                array[i] = running_process;
                            }
                        }
                        count++;
                        if (count==array.length)
                        {
                            time++;
                            System.out.print("quantum time for processes at time "+ time + ": ( " );
                            for (process p : array){
                                System.out.print(p.getAg_quantum() + ", ");
                            }
                            System.out.print(")");
                            System.out.println();

                            break mainloop;
                        }

                        break outerloop;
                    }
                }


                /////////////// taking copy from the current queue to check priority ////////////////////////

                process[] temp_process_array = new process[queue.size()];
                for (int f = 0; f < temp_process_array.length; f++) {
                    temp_process_array[f] = new process();
                }
                for (int m = 0; m < temp_process_array.length; m++) {
                    temp_process_array[m] = queue.remove(); // now the queue is empty (processes are in the array)

                }
                ///////////////// check priority ////////////////////////
                process ptemp = new process();
                ptemp.setPriority(10000000);
                ptemp.setProcess_name("no priority/burst smaller found");
                int index = -1;
                Boolean found_higher_priority = false;
                for (int l = 0; l < temp_process_array.length; l++) {
                    if (temp_process_array[l].getPriority() < running_process.getPriority()) {
                        if (temp_process_array[l].getPriority() < ptemp.getPriority()) // compare with running process then compare with smallest found element
                        {
                            ptemp = temp_process_array[l]; // process to execute if found with smaller priority
                            index = l;
                            found_higher_priority = true;
                        }
                    }

                }
                ///////////// replace the running process with the higher priority process //////////////////
                int remaining_quantum = 0;

                if (!found_higher_priority) // the process will continue to 50% exec
                {
                    for (int m = 0; m < temp_process_array.length; m++) {
                        queue.add(temp_process_array[m]);
                    }
                } else {

                    queue.add(ptemp); // found process with the highest priority

                    for (int m = 0; m < temp_process_array.length; m++) {
                        if (m != index) // we already added this process to the head of the queue
                        {
                            queue.add(temp_process_array[m]);
                        }

                    }

                    remaining_quantum = (ag_quantum - ceil25)/2 ;

                    running_process.setAg_quantum(remaining_quantum + ag_quantum);

                    // updating quantum in the array
                    for (int i = 0; i < array.length; i++){
                        if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                            array[i].setAg_quantum(remaining_quantum + ag_quantum);
                        }
                    }


                    queue.add(running_process);


                    time--;
                    System.out.print("quantum time for processes at time "+ time + ": ( " );
                    for (process p : array){
                        System.out.print(p.getAg_quantum() + ", ");
                    }
                    System.out.print(")");
                    System.out.println();

                    break;  // break outerloop

                }

                //////// if the current process has the highest priority we will continue processing to 50% of its quantum //////////
                double half = 0.5 * running_process.getAg_quantum();
                int ceil50 = (int) Math.ceil(half);
                int halff= (int) Math.ceil(half);
                ceil50 = ceil50 - ceil25;
                for (int l = 0; l < ceil50; l++) {
                    running_process.set_remaining_burst(--temp_remaining_burst);
                    time++;
                    elapsed_quantum++;
                    if (process_queue_count < array.length) {
                        if (array[process_queue_count].get_arrival_time() == time) {
                            queue.add(array[process_queue_count]);
                            process_queue_count++;
                        }
                    }
                    if (running_process.get_remaining_burst() == 0) {
                        running_process.set_finish_time(time);
                        int turn_around;
                        running_process.setTurnaround_time(running_process.get_finish_time() - running_process.get_arrival_time());
                        turn_around = running_process.get_turnaround_time();
                        int process_time;
                        process_time = running_process.getBurst_time();
                        running_process.setWaiting_time(turn_around - process_time);
                        time--;
                        running_process.setAg_quantum(0);
                        // updating quantum in the array
                        for (int i = 0; i < array.length; i++){
                            if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                                array[i].setAg_quantum(0);
                            }
                        }


                        // Logging the info into the array
                        for (int i = 0; i < array.length; i++) {
                            if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                                array[i] = running_process;
                            }
                        }
                        count++;
                        if (count==array.length)
                        {
                            time++;
                            System.out.print("quantum time for processes at time "+ time + ": ( " );
                            for (process p : array){
                                System.out.print(p.getAg_quantum() + ", ");
                            }
                            System.out.print(")");
                            System.out.println();


                            break mainloop;
                        }
                        break outerloop;
                    }


                }
                ////////// we need to  check the process with the smallest burst time //////////////////////

                for (int m = 0; m < temp_process_array.length; m++) {
                    temp_process_array[m] = queue.remove();
                }
                ptemp.set_remaining_burst(100000);
                index = -1;
                Boolean found_lower_burst = false;
                for (int l = 0; l < temp_process_array.length; l++) {
                    if (temp_process_array[l].get_remaining_burst() < running_process.get_remaining_burst()) {
                        if (temp_process_array[l].get_remaining_burst() < ptemp.get_remaining_burst()) {
                            ptemp = temp_process_array[l];
                            index = l;
                            found_lower_burst = true;
                        }

                    }

                }
                ///////////// replace the running process with the lower burst process //////////////////

                if (!found_lower_burst) {
                    for (int m = 0; m < temp_process_array.length; m++) {
                        queue.add(temp_process_array[m]);
                    }
                } else {
                    queue.add(ptemp);

                    for (int m = 0; m < temp_process_array.length; m++) {
                        if (m != index) {
                            queue.add(temp_process_array[m]);
                        }
                    }
                    remaining_quantum = ag_quantum - halff;
                    running_process.setAg_quantum(remaining_quantum + ag_quantum);
                    // updating quantum in the array
                    for (int i = 0; i < array.length; i++){
                        if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                            array[i].setAg_quantum(remaining_quantum + ag_quantum);
                        }
                    }
                    queue.add(running_process);
                    time--;
                    System.out.print("quantum time for processes at time "+ time + ": ( " );
                    for (process p : array){
                        System.out.print(p.getAg_quantum() + ", ");
                    }
                    System.out.print(")");
                    System.out.println();

                    break; //breaking outerloop
                }
                //////// if the current process has the lowest burst we will continue processing to 100% of its quantum //////////
                for (int l = elapsed_quantum; l < running_process.getAg_quantum(); l++) {
                    running_process.set_remaining_burst(--temp_remaining_burst);
                    time++;
                    if (process_queue_count < array.length) {
                        if (array[process_queue_count].get_arrival_time() == time) {
                            queue.add(array[process_queue_count]);
                            process_queue_count++;
                        }
                    }
                    if (running_process.get_remaining_burst() == 0) {
                        running_process.set_finish_time(time);
                        int turn_around;
                        running_process.setTurnaround_time(running_process.get_finish_time() - running_process.get_arrival_time());
                        turn_around = running_process.get_turnaround_time();
                        int process_time;
                        process_time = running_process.getBurst_time();
                        running_process.setWaiting_time(turn_around - process_time);
                        time--;
                        System.out.print("quantum time for processes at time "+ time + ": ( " );
                        for (process p : array){
                            System.out.print(p.getAg_quantum() + ", ");
                        }
                        System.out.print(")");
                        System.out.println();

                        running_process.setAg_quantum(0);
                        // updating quantum in the array
                        for (int i = 0; i < array.length; i++) {
                            if (Objects.equals(running_process.getProcess_name(),array[i].getProcess_name()))
                            {
                                array[i].setAg_quantum(0);
                            }

                        }


                        // Logging the info into the array
                        for (int i = 0; i < array.length; i++) {
                            if (Objects.equals(running_process.getProcess_name(), array[i].getProcess_name())){
                                array[i] = running_process;
                            }
                        }
                        count++;
                        if (count==array.length)
                        {
                            time++;
                            System.out.print("quantum time for processes at time "+ time + ": ( " );
                            for (process p : array){
                                System.out.print(p.getAg_quantum() + ", ");
                            }
                            System.out.print(")");
                            System.out.println();


                            break mainloop;
                        }
                        break outerloop;
                    }

                }

                if (running_process.get_remaining_burst() > 0)
                {
                    ag_quantum=running_process.getAg_quantum();
                    ag_quantum=ag_quantum+2;
                    running_process.setAg_quantum(ag_quantum);

                    // updating quantum in the array
                    for (int i = 0; i < array.length; i++) {
                        if (Objects.equals(running_process.getProcess_name(),array[i].getProcess_name()))
                        {
                            array[i].setAg_quantum(ag_quantum );
                        }

                    }
                    queue.add(running_process);
                }
                time--;
                System.out.print("quantum time for processes at time "+ time + ": ( " );
                for (process p : array){
                    System.out.print(p.getAg_quantum() + ", ");
                }
                System.out.print(")");
                System.out.println();

            }

        }


        System.out.print("Execcution Order: ");
        for (String str : execution_order ){
            System.out.print(str + " ");
        }
        System.out.println();

        for (process p : array){
            p.print_attributes();
            System.out.println("--------------------");
        }

        get_average_turnaround_time(array);
        get_average_waiting_time(array);


    }

    public void get_average_waiting_time(process[] process_array) {
        double average;
        double sum = 0;
        for (process i : process_array) {
            sum += i.getWaiting_time();

        }
        average = sum / process_array.length;
        System.out.println("Average waiting time: " + average);
    }

    public void get_average_turnaround_time(process[] process_array) {
        double average;
        double sum = 0;
        for (process i : process_array) {
            sum += i.get_turnaround_time();

        }
        average = sum / process_array.length;
        System.out.println("Average turnaround time: " + average);

    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);

        System.out.print("Enter number of processes: ");

        int num = scn.nextInt();

        process[] process_array = new process[num];
        for (int i = 0; i < num; i++) {
            process_array[i] = new process();
        }


        int arrival_time, burst_time, priority, ag_quantum;
        String name;

        for (int i = 0; i < num; i++) {

            System.out.print("Enter name of process " + (i + 1) + ": ");
            name = scn.next();

            System.out.print("Enter burst time of process " + (i + 1) + ": ");
            burst_time = scn.nextInt();

            System.out.print("Enter arrival time of process " + (i + 1) + ": ");
            arrival_time = scn.nextInt();

            System.out.print("Enter priority of process " + (i + 1) + ": ");
            priority = scn.nextInt();

            System.out.print("Enter quantum time of process " + (i + 1) + ": ");
            ag_quantum = scn.nextInt();

            process_array[i].set_process_attributes(name, arrival_time, burst_time, priority,ag_quantum );
        }

        // Rearranging processes by their arrival time
        process temp;

        for(int i=0; i<process_array.length;i++)
        {
            for(int j=i+1; j<process_array.length;j++)
            {
                if (process_array[i].arrival_time > process_array[j].arrival_time)
                {
                    temp = process_array[i];
                    process_array[i]=process_array[j];
                    process_array[j]=temp;
                }
            }
        }


        process[] AG_array;
        AG_array = process_array.clone();
        AG_scheduling ag = new AG_scheduling();
        ag.ag_sch(AG_array);









    }
}