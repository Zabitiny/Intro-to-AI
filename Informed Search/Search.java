import java.util.Set;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Arrays;

public class Search extends Problem {

    public static void AStar(Problem prob, boolean heur, boolean exp) {
        Node node = new Node(prob, heur);
        PriorityQueue<Node> frontier = new PriorityQueue<Node>();
        frontier.add(node);
        Set<Node> explored = new HashSet<Node>();
        int nodeCounter = 1;

        while(true) {
            if(frontier.isEmpty()) {
                System.out.println("fail");
                return;
            }
            node = frontier.poll();
            
            if(prob.goalTest(node.state)) {
                System.out.println("Success: " 
                    + Arrays.toString(node.state) +" Depth: "
                    + node.pathCost + " Search Cost: " + nodeCounter);
                success(node);
                return;
            }
            if(node.pathCost > 24) {
                System.out.println("too deep");
                return;
            }
            if(exp) explored.add(node);
            
            //generate successors
            for(Action act : prob.generateActions(node.state)) {
                Node child = new Node(prob, node, act, heur);
                if(exp && !explored.contains(child)) {
                    frontier.add(child);
                    nodeCounter++;
                }
                else if(!exp) {
                    frontier.add(child);
                    nodeCounter++;
                }
            }
        }
    }

    //for printing out path of nodes to success
    private static void success(Node node) {
        Node prev = null, curr = node, next=node;
        while(curr != null) {
            next = curr.parent;
            curr.parent = prev;
            prev = curr;
            curr = next;
        }
        curr = prev;        
        while(curr != null) {
            System.out.println(Arrays.toString(curr.state));
            curr = curr.parent;
        }
    }

    private static class Node implements Comparable<Node> {
        private int[] state;
        private Integer estCost;
        private int pathCost;
        private Node parent;
        private int hashCode = 0;

        // Constructor for initial node
        public Node(Problem prob, boolean heur) {
            state = Arrays.copyOf(prob.getInitialState(), getSize());
            pathCost = 0;
            estCost = pathCost + (heur? hamming() : manhattan());
            parent = null;
        }
        
        // Constructor for successor nodes
        public Node(Problem prob, Node node, Action act, boolean heur) {
            state = prob.transition(node.state, act);
            pathCost = node.pathCost +1;
            estCost = pathCost + (heur? hamming() : manhattan());
            parent = node;
        }

        private int hamming() {
            int counter = 0;
            for(int i : state) {
                if(state[i] != i && state[i] != 0) {
                    counter++;
                }
            }
            return counter;
        }

        private int manhattan() {
            int counter = 0;
            for(int i : state) {
                if(state[i] != i && state[i] != 0) {
                    int delta = Math.abs(i - state[i]);
                    counter += delta/3 + delta%3;
                }
            }
            return counter;
        }

        @Override
        public int compareTo(Node n) {
            return estCost - n.estCost;
        }

        @Override
        public int hashCode() {
            if(hashCode == 0) 
                for(int i=0; i < state.length; i++) 
                    hashCode += 2*hashCode + state[i];
                    
            return hashCode;
        }
    }
}