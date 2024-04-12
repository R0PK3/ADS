
import java.util.LinkedList;

import java.util.TreeSet;

import java.util.Comparator;

public class prims {

    //kaimynystes sarasas
    class node1 {

        // Saugo destination virsune kaimynystes sarase
        int dest;
        //Saugo virsunes reiksme (svori) kaimynystes sarase
        int weight;
        // Konstruktorius
        node1(int a, int b) {

            dest = a;
            weight = b;
        }
    }

    static class Graph {

        // Virsuniu kiekis grafe
        int V;
        // Kaimynystes sarasas is duotu virsuniu
        LinkedList<node1>[] adj;

        // Konstruktorius
        Graph(int e) {

            V = e;
            adj = new LinkedList[V];

            for (int o = 0; o < V; o++){

                adj[o] = new LinkedList<>();
            }
        }
    }

    //klase atstovaujanti "mazga" PriorityQueue
    //Saugo virsune ir jos atitikmeni
    //key value
    class node {

        int vertex;
        int key;
    }

    // Sukurta comparator klase priorityQueue
    // kuri grazina 1, jeigu node0.key > node1.key
    // arba grazina 0, jei node0.key < node1.key
    // grazina -1 kitu atveju
    class comparator implements Comparator<node> {

        @Override
        public int compare(node node0, node node1) {

            return node0.key - node1.key;
        }

    }

    // metodas skirtas prideti briaunai su nurodytom reiksmem
    void addEdge(Graph graph, int src, int dest, int weight) {

        node1 node0 = new node1(dest, weight);

        node1 node = new node1(src, weight);

        graph.adj[src].addLast(node0);

        graph.adj[dest].addLast(node);
    }


    // metodas skirtas surasti minimaliausiam medziui (minimal tree)
    void prims_mt(Graph graph)
    {
        // Ar virsune yra priorityQueue ar ne
        Boolean[] mtset = new Boolean[graph.V];
        // virsuniu node'as
        node[] e = new node[graph.V];
        // Saugo virsunes "tevus"
        int[] parent = new int[graph.V];

        // kuriamas virsuniu node'as atitinkantis virsuniu skaiciu (uzpildomas masyvas)
        for (int o = 0; o < graph.V; o++) {

            e[o] = new node();

        }
        // inicializacija
        for (int o = 0; o < graph.V; o++) {

            mtset[o] = false;

            // Key reiksmes inicializuojamos iki begalybes

            e[o].key = Integer.MAX_VALUE;

            e[o].vertex = o;

            parent[o] = -1;

        }

        // Itraukiama source virsune i mtset
        mtset[0] = true;
        // key reiksme nustatoma i 0, nes ji bus isimta pati pirma is priorityQueue
        e[0].key = 0;

        // Naudojamas TreeSet'as vietoj PriorityQueue kaip pasalinimo funkcija is priorityQueue
        TreeSet<node> queue = new TreeSet<node>(new comparator());

        // Eiles sukurimas
        for (int o = 0; o < graph.V; o++) {

            queue.add(e[o]);
        }

        // Ciklas iki kol eile nepasidaro tuscia
        while (!queue.isEmpty()) {

            // Isimamas node'as su maziausia key reiksme

            node node0 = queue.pollFirst();

            // Ta node'a idedam i mtset

            mtset[node0.vertex] = true;

            // Visos kitos likusios kaimynynes isimtos virsunes V
            // : reiskia iki
            for (node1 iterator : graph.adj[node0.vertex]) {

                // Jeigu V yra eileje

                if (mtset[iterator.dest] == false) {

                    // Jeigu key reiksme kaimyno virsunes yra didesne nei isimta key reiksme
                    // atnaujinama key reiksme kaimynystes virsunese
                    // isimama pirma ir pridedama atnaujinta virsune

                    if (e[iterator.dest].key > iterator.weight) {

                        queue.remove(e[iterator.dest]);

                        e[iterator.dest].key = iterator.weight;

                        queue.add(e[iterator.dest]);

                        parent[iterator.dest] = node0.vertex;

                    }

                }

            }

        }

        // Spausdinamos minimalaus medzio virsuniu poros

        for (int o = 1; o < graph.V; o++) {

            System.out.println(parent[o] + " " + "-" + " " + o);
        }
    }

    public static void main(String[] args) {
        //virsuniu kiekis
        int V = 10;

        // sukuriamas graph objektas
        Graph graph = new Graph(V);

        // sukuriamas sarasas
        prims e = new prims();

        // i grafa idedamos reiksmes (16 nodes)
        e.addEdge(graph, 0, 1, 4);
        e.addEdge(graph, 0, 7, 8);
        e.addEdge(graph, 1, 2, 8);
        e.addEdge(graph, 1, 7, 11);
        e.addEdge(graph, 2, 3, 7);
        e.addEdge(graph, 2, 8, 2);
        e.addEdge(graph, 2, 5, 4);
        e.addEdge(graph, 3, 4, 9);
        e.addEdge(graph,3,9,20);
        e.addEdge(graph, 3, 5, 14);
        e.addEdge(graph, 4, 5, 10);
        e.addEdge(graph,4,9,4);
        e.addEdge(graph, 5, 6, 2);
        e.addEdge(graph, 6, 7, 1);
        e.addEdge(graph, 6, 8, 6);
        e.addEdge(graph, 7, 8, 7);

        // ieskomas ir sukuriamas minimalus medis
        e.prims_mt(graph);
    }
}