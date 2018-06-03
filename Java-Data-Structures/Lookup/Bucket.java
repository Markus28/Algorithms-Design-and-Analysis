package Lookup;

import java.util.LinkedList;



public class Bucket<K, E>
{
    private LinkedList<K> keys;
    private LinkedList<E> vals;


    public Bucket()
    {
       keys = new LinkedList<>();
       vals = new LinkedList<>();
    }


    public E get(K x)
    {
        for(int i = 0; i < keys.size(); i++)
        {
            if(keys.get(i).equals(x))
            {
                return vals.get(i);
            }
        }
        
        return null;
    }
    
    public void add(K x, E y)
    {
        if(get(x) == null)
        {
            keys.add(x);
            vals.add(y);
        }
        else{
            for(int i = 0; i < keys.size(); i++)
            {
                if(keys.get(i).equals(x))
                {
                    vals.set(i, y);
                }
            }
        }
    }
    
    public void remove(K x)
    {
        for(int i = 0; i < keys.size(); i++)
        {
            if(keys.get(i).equals(x))
            {
                keys.remove(i);
                vals.remove(i);
                break;
            }
        }
    }
}
