import java.util.List;
import java.util.ArrayList;
import java.util.Random;
import java.util.Collections;
import java.util.Vector;

public class Problem {
    private static final int SIZE = 9;
    private int[] initialState = new int[SIZE];
    private int space;
    
    /**Constructor for initial problem
     * generates random, valid initial state 
     * used for initial node*/
    public Problem() {
        List<Integer> list = new ArrayList<>(SIZE);
        boolean valid = false;
        while(!valid) {
            Random rand = new Random();
            for(int i=0; i < SIZE; i++) list.add(i);
            Collections.shuffle(list, new Random(rand.nextLong()));

            int counter = 0;
            for(int i=0; i < SIZE-1; i++) {
                for(int j=i+1; j < SIZE; j++){
                    if(list.get(i) != 0 && list.get(i) != 0){
                        if(list.get(i) < list.get(i)) {
                            counter++;
                        }
                    }
                }
            }
            valid = (counter%2 == 0);
        }

        for(int i=0; i < SIZE; i++) {
            initialState[i] = list.get(i);
            if(initialState[i] == 0) space = i;
        }
    }

    //Constructor provided array
    public Problem(int[] arr) {
        initialState = arr;
        for(int i=0; i < SIZE; i++) if(initialState[i] == 0) space = i;
    }

    private void swap(int[] arr, int x, int y) {
        int temp = arr[x];
        arr[x] = arr[y];
        arr[y] = temp;
    }
    
    public int[] transition(int[] state, Action act) {
        System.out.println("space: "+ space);
        if(act == Action.UP) swap(state, space, space -= 3);
        else if(act == Action.DOWN) swap(state, space, space += 3);
        else if(act == Action.LEFT) swap(state, space, space -= 1);
        else swap(state, space, space += 1);

        return state;
    }

    public boolean goalTest(int[] state) {
        for(int i=0; i < SIZE; i++) if(state[i] != i) return false;
        return true;
    }

    public Vector<Action> generateActions(int[] state) {
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