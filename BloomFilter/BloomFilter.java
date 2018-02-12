import java.util.Random;


public class BloomFilter
{
    private int n;
    private int k;
    private int[] salts;
    private boolean[] filter;

    public BloomFilter(int n, int k)
    {
        this.n = n;
        this.k = k;
        filter = new boolean[n];
        salts = new int[k];
        Random rand = new Random();
        
        for(int i = 0; i < k; i++)
        {
            salts[i] = rand.nextInt(10000) - 5000;
        }
    }
    
    public boolean get(Object key)
    {
        for(int salt: salts)
        {
            if(!filter[hash(key.hashCode() + salt)%n])
            {
                return false;
            }
        }
        
        return true;
    }
    
    public void set(Object key)
    {
        for(int salt: salts)
        {
            filter[hash(key.hashCode() + salt)%n] = true;
        }
    }
    
    public int hash(int x)
    {
        x = ((x >> 16)^x)*0x45d9f3b;
        x = ((x >> 16)^x)*0x45d9f3b;
        x = (x >> 16)^x;
        return x;
    }
}
