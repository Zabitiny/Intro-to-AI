import java.util.Arrays;
import java.util.Scanner;

public class AStarDriver extends Search {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        boolean run = true;
        while(run){
            System.out.println("Would you like to test? (enter 'yes' or 'no') ");
            boolean valid = false;  //valid input from user
            boolean test = false;   //whether to run test sequence or single sequence
            while(!valid){    
                String input = scan.nextLine();
                if(input.equalsIgnoreCase("yes")) {
                    test = true;
                    valid = true;
                }
                else if(input.equalsIgnoreCase("no")) {
                    test = false;
                    valid = true;
                }
                else System.out.print("\nEnter something valid (enter 'yes' or 'no'): ");
            }

            System.out.println("Which heuristic would you like to use?");
            System.out.println("1) Hamming");
            System.out.println("2) Manhatton");
            boolean heur = true;
            valid = false;
            while(!valid){
                try {
                    String line = scan.nextLine();
                    int input = Integer.parseInt(line);
                    if(input == 1) {
                        heur = true;
                        valid = true;
                    }
                    else if(input == 2) {
                        heur = false;
                        valid = true;
                    }
                    else System.out.print("\nEnter something valid (enter 1 or 2): ");
                } catch(NumberFormatException e) {
                    System.out.print("\nEnter something valid (enter 1 or 2): ");
                }
            }

            System.out.println("Which type of search would you like to use?");
            System.out.println("1) Graph");
            System.out.println("2) Tree");
            boolean graph = true;
            valid = false;
            while(!valid){
                try{
                    String line = scan.nextLine();
                    int input = Integer.parseInt(line);
                    if(input == 1) {
                        graph = true;
                        valid = true;
                    }
                    else if(input == 2) {
                        graph = false;
                        valid = true;
                    }
                    else System.out.print("\nEnter something valid (enter 1 or 2): ");
                } catch(NumberFormatException e) {
                    System.out.print("\nEnter something valid (enter 1 or 2): ");
                }
            }
            if(test) {
                System.out.println("Running tests now\n");
                for(int i=1; i <= 1000; i++) {
                    Problem prob = new Problem();
                    System.out.print("Test "+i+": ");
                    double start = System.nanoTime();
                    AStar(prob, heur, graph, test);
                    System.out.println("Time: "+ (System.nanoTime() - start)/1000000000 +" seconds");
                }
            }
            else{
                valid = false;
                while(!valid) {
                    try {
                        System.out.println("What puzzle would you like to solve?");
                        System.out.println("1) Random puzzle");
                        System.out.println("2) Manually enter it");
                        String line = scan.nextLine();
                        int choice = Integer.parseInt(line);
                        if(choice == 1){
                            valid = true;
                            Problem prob = new Problem();
                            System.out.println("running algorithm now with inital state: "
                                + Arrays.toString(prob.getInitialState()));
                            AStar(prob, heur, graph, test);
                        }
                        else if(choice == 2) {
                            int n = getSize();
                            int[] arr = new int[n];
                            boolean range = false;      //flag for numbers are in range
                            boolean duplicate = false;  //flag for duplicate numbers
                            while(!valid){
                                try {
                                    System.out.print("Enter your values: ");
                                    String input = scan.nextLine();
                                    String[] numbers = input.split(" ");
                                    for(int i=0; i < n; i++) {
                                        arr[i] = Integer.parseInt(numbers[i]);
                                        if(arr[i] > 8 || arr[i] < 0) {
                                            range = true;
                                            break;
                                        }
                                    }
                                    for(int i=0; i < n; i++)
                                        for(int j=i+1; j < n; j++)
                                            if(arr[i] == arr[j]) duplicate = true;
                                    
                                    int counter=0;
                                    for(int i=0; i < n-1; i++) {
                                        for(int j=i+1; j < n; j++){
                                            if(arr[i] != 0 && arr[j] != 0){
                                                if(arr[j] < arr[i]) {
                                                    counter++;
                                                }
                                            }
                                        }
                                    }
                                    valid = (counter%2 == 0) ? true : false;
                                    if(range) {
                                        System.out.println("You entered a number outside the range - your values should be between 0 and 8 (inclusive)");
                                        System.out.println("Try again: ");
                                        valid = false;
                                        range = false;
                                        duplicate = false;
                                    }
                                    else if(duplicate) {
                                        System.out.println("You entered duplicate numbers");
                                        valid = false;
                                        range = false;
                                        duplicate = false;
                                    }
                                    else if(valid){
                                        System.out.println("Running algorithm now");
                                        Problem prob = new Problem(arr);
                                        AStar(prob, heur, graph, test);
                                    }
                                    else System.out.println("\nYou did not enter a solvable array. Try again: ");
                                } catch(IndexOutOfBoundsException e) {
                                    System.out.println("\nYou entered too many or too little values. Try again: ");
                                    valid = false;
                                } catch(NumberFormatException e) {
                                    System.out.println("\nYou entered something that wasn't a number. Try again: ");
                                }
                            }
                        }
                        else System.out.print("\nEnter something valid(1 or 2): ");
                    } catch(NumberFormatException e) {
                        System.out.print("\nEnter something valid(1 or 2): ");
                    }
                }
            }//end single run

            System.out.println("Would you like to run again?");
            System.out.println("Enter choice (yes or no): ");
            valid = false;
            while(!valid) {
                String input = scan.nextLine();
                if(input.equalsIgnoreCase("yes")) valid = true;
                else if(input.equalsIgnoreCase("no")) {
                    valid = true;
                    run = false;
                }
                else System.out.println("Enter something valid (yes or no) ");
            }
        }//end run

        System.out.println("PROGRAM TERMINATED");
        scan.close();
    }
}