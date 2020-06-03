import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Collections;
import java.util.Vector;

public class Problem {
    private static final int SIZE = 9;
    private int[] initialState = new int[SIZE];
    
    /**Constructor for initial problem
     * generates random, valid initial state 
     * used for initial node*/
    public Problem() {
        List<Integer> list = new ArrayList<>(SIZE);
        boolean valid = false;
        while(!valid) {
            list.clear();
            Random rand = new Random();
            for(int i=0; i < SIZE; i++) list.add(i);
            Collections.shuffle(list, new Random(rand.nextLong()));

            int counter = 0;
            for(int i=0; i < SIZE-1; i++) {
                for(int j=i+1; j < SIZE; j++){
                    if(list.get(i) != 0 && list.get(j) != 0){
                        if(list.get(j) < list.get(i)) {
                            counter++;
                        }
                    }
                }
            }
            valid = (counter%2 == 0);
        }
        for(int i=0; i < SIZE; i++) initialState[i] = list.get(i);
        System.out.println("initial state: "+ Arrays.toString(initialState));
    }

    //Constructor provided array
    public Problem(int[] arr) {
        initialState = arr;
    }

    public void swap(int[] arr, int x, int y) {
        int temp = arr[x];
        arr[x] = arr[y];
        arr[y] = temp;
    }

    public boolean goalTest(int[] state) {
        for(int i=0; i < SIZE; i++) if(state[i] != i) return false;
        return true;
    }

    public Vector<Action> generateActions(int[] state, int space) {
        Vector<Action> actions = new Vector<Action>();

        if(space > 2) actions.add(Action.UP);
        if(space < 6) actions.add(Action.DOWN);
        if(space%3 != 0) actions.add(Action.LEFT);
        if(space%3 != 2) actions.add(Action.RIGHT);
        return actions;
    }

    public int[] getInitialState() {
        return initialState;
    }

    public static int getSize() {
        return SIZE;
    }

    public enum Action {
        UP, DOWN, LEFT, RIGHT;
    }
}