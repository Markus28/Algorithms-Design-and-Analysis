import java.util.LinkedList;



public class Bucket
{
    private LinkedList keys;
    private LinkedList vals;


    public Bucket()
    {
       keys = new LinkedList();
       vals = new LinkedList();
    }


    public Object get(Object x)
    {
        for(int i = 0; i < keys.size(); i++)
        {
            if(keys.get(i) == x)
            {
                return vals.get(i);
            }
        }
        
        return null;
    }
    
    public void add(Object x, Object y)
    {
        if(get(x) == null)
        {
            keys.add(x);
            vals.add(y);
        }
        else{
            for(int i = 0; i < keys.size(); i++)
            {
                if(keys.get(i) == x)
                {
                    vals.set(i, y);
                }
            }
        }
    }
    
    public void remove(Object x)
    {
        for(int i = 0; i < keys.size(); i++)
        {
            if(keys.get(i) == x)
            {
                keys.remove(i);
                vals.remove(i);
                break;
            }
        }
    }
}
