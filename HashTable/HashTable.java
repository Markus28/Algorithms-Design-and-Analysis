public class HashTable
{
    private Bucket[] map;
    private int buckets;

    public HashTable(int buckets)
    {
        this.buckets = buckets;
        map = new Bucket[buckets];
        for(int i = 0; i < buckets; i++)
        {
            map[i] = new Bucket();
        }
    }

    public Object get(Object key)
    {
        return map[toIndex(key.hashCode())].get(key);
    }
    
    public void add(Object key, Object val)
    {
        map[toIndex(key.hashCode())].add(key, val);
    }
    
    public void remove(Object key)
    {
        map[toIndex(key.hashCode())].remove(key);
    }
    
    public int toIndex(int k)
    {
        return (k*(k+3))%buckets;
    }
}
