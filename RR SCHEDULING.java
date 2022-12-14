import javax.lang.model.type.NullType;
import java.util.*;
import java.lang.Math;

import static java.lang.Math.ceil;

class process{
    String process_name;
    int arrival_time, burst_time, remaining_burst, waiting_time, finish_time, turnaround_time;

    public void set_process_attributes(String process_name, int arrival_time, int burst_time)
    {
        this.process_name = process_name;
        this.arrival_time = arrival_time;
        this.burst_time = burst_time;

        remaining_burst = burst_time;
        finish_time = 0;
        waiting_time = 0;
        turnaround_time=0;
    }
    public void print_attributes(){
        System.out.println("name: " + process_name);
        System.out.println("arrival time: " + arrival_time);
        System.out.println("burst time: " + burst_time);

        System.out.println("waiting time: " + waiting_time);
        System.out.println("finish time " + finish_time);
        System.out.println("turnaround time: " + turnaround_time);
    }
    //////////////////////////////////// setters and getters ////////////////////////////////////////




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



    public String getProcess_name() {
        return process_name;
    }

    public void setProcess_name(String process_name) {
        this.process_name = process_name;
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


}

class round_robin{
    public process[] round_robin_scheduling(process[] array,int quantum_time,int context_switch){
        Queue<process> queue = new LinkedList<>();
        process[] process_array = new process[array.length];
        for (int i = 0; i < array.length; i++) {
            process_array[i] = new process();
        }


        process temp;
        int count=0;
        int k=0;
        System.out.println("----------- RR SCHEDULING------------ ");
        System.out.println("Execcution Order: ");
        for (int i=0; i<1000;i++)
        {
            if (k<array.length) {
                if (array[k].get_arrival_time() == i) {
                    queue.add(array[k]);
                    k++;
                }
            }
            if (queue.isEmpty())
            {
                continue;
            }
            temp=queue.remove();
            System.out.print(temp.getProcess_name() + " ");



            for (int j = 0; j < quantum_time; j++) {
                int temp_remaining_burst=temp.get_remaining_burst();
                temp.set_remaining_burst(--temp_remaining_burst);
                i++;
                if (k<array.length) {
                    if (array[k].get_arrival_time() == i) {
                        queue.add(array[k]);
                        k++;
                    }
                }
                if (temp.get_remaining_burst()==0)
                {
                    for (int l = 0; l < context_switch; l++) {
                        i++;
                        if (k<array.length) {
                            if (array[k].get_arrival_time() == i) {
                                queue.add(array[k]);
                                k++;
                            }
                        }
                    }
                    temp.set_finish_time(i);
                    int turn_around;
                    temp.setTurnaround_time(temp.get_finish_time() - temp.get_arrival_time());
                    turn_around=temp.get_turnaround_time();
                    int process_time;
                    process_time=temp.getBurst_time();
                    temp.setWaiting_time(turn_around - process_time);
                    //temp.print_attributes();
                    for (int l = 0; l < array.length; l++) {
                        if (Objects.equals(array[l].getProcess_name(), temp.getProcess_name()))
                        {
                            array[l]=temp;
                            break;
                        }
                    }
                    count++;
                    i--;

                    break;
                }
            }
            if (temp.get_remaining_burst() > 0)
            {
                queue.add(temp);
                for (int l = 0; l < context_switch; l++) {
                    i++;
                    if (k<array.length) {
                        if (array[k].get_arrival_time() == i) {
                            queue.add(array[k]);
                            k++;
                        }
                    }

                }
                i--;
            }
            if (count == array.length)
            {
                break;
            }
        }
        System.out.println();

        for (int i = 0; i < array.length; i++) {
            //System.out.println(i);
            array[i].print_attributes();
        }


        get_average_waiting_time(array);
        get_average_turnaround_time(array);


        return process_array;
    }

    public void get_average_waiting_time(process[] process_array){
        double average;
        double sum = 0;
        for (process i : process_array) {
            sum += i.getWaiting_time();

        }
        average=sum/process_array.length;
        System.out.println("Average waiting time: "+average);
    }
    public void get_average_turnaround_time(process[] process_array){
        double average;
        double sum= 0;
        for (process i : process_array) {
            sum += i.get_turnaround_time();

        }
        average=sum/process_array.length;
        System.out.println("Average turnaround time: "+average);
    }


} //Done


public class Main {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);

        System.out.print("Enter number of processes: ");

        int num = scn.nextInt();

        process[] process_array = new process[num];
        for (int i = 0; i < num; i++) {
            process_array[i] = new process();
        }

        System.out.print("Enter quantum time for RR : ");
        int quantum_time = scn.nextInt();

        System.out.print("Enter context switching time: ");
        int context_switch = scn.nextInt();


        int arrival_time, burst_time;
        String name;

        for (int i = 0; i < num; i++) {

            System.out.print("Enter name of process " + (i + 1) + ": ");
            name = scn.next();

            System.out.print("Enter burst time of process " + (i + 1) + ": ");
            burst_time = scn.nextInt();

            System.out.print("Enter arrival time of process " + (i + 1) + ": ");
            arrival_time = scn.nextInt();

            process_array[i].set_process_attributes(name, arrival_time, burst_time);
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

        process[] round_robin_array;
        round_robin_array = process_array.clone();
        round_robin rr = new round_robin();
        rr.round_robin_scheduling(round_robin_array, quantum_time,context_switch);













    }
}