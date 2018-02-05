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
        return map[key.hashCode()%buckets].get(key);
    }
    
    public void add(Object key, Object val)
    {
        map[key.hashCode()%buckets].add(key, val);
    }
    
    public void remove(Object key)
    {
        map[key.hashCode()%buckets].remove(key);
    }
}
