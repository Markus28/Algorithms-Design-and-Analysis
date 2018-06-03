package Lookup;

public class Test {

    public static void main(String[] args)
    {
        HashTable<String, Integer> ht = new HashTable<>(2000);
        ht.add("A", 1);
        ht.add("B", 2);
        System.out.println(ht.get("B"));
        ht.remove("A");
        System.out.println(ht.get("A"));

        BloomFilter<String> bf = new BloomFilter<>(3000, 4);
        bf.set("hey");
        bf.set("world");
        System.out.println(bf.get("hey") && bf.get("world"));
        System.out.println(bf.get("foo") || bf.get("bar"));
    }
}
