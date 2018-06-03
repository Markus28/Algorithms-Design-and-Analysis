package Lookup;


public class HashTable<K, E>
{
    private Bucket<K, E>[] map;
    private int buckets;

    public HashTable(int buckets)
    {
        this.buckets = buckets;

        map = new Bucket[buckets];

        for(int i = 0; i < buckets; i++)
        {
            map[i] = new Bucket<>();
        }
    }

    public E get(K key)
    {
        return map[toIndex(key.hashCode())].get(key);
    }
    
    public void add(K key, E val)
    {
        map[toIndex(key.hashCode())].add(key, val);
    }
    
    public void remove(K key)
    {
        map[toIndex(key.hashCode())].remove(key);
    }
    
    private int toIndex(int k)
    {
        return Math.abs((k*(k+3)))%buckets;
    }
}
