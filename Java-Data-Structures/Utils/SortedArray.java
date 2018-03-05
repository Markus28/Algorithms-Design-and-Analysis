package Utils;

public class SortedArray<T extends Comparable <T>>
{
    private T[] arr;
    
    public SortedArray(T[] arr)
    {
        this.arr = arr;
    }

    public T get(int i)
    {
        return arr[i];
    }
    
    public boolean exists(T obj)
    {
        return get(approximateSearchBasic(obj, 0, arr.length - 1)).equals(obj);
    }
    
    protected int approximateSearchBasic(T obj, int lower, int upper)
    {
        int i = (lower + upper)/2;
        
        while(upper >= lower)
        {
            if(arr[i].equals(obj))
            {
                return i;
            }
            
            else if (arr[i].compareTo(obj) > 0)
            {
                upper = i-1;
            }
            
            else
            {
                lower = i+1;
            }
            
            i = (upper + lower)/2;
        }
        
        if(arr[lower].compareTo(obj) <= 0)
        {
            return lower;
        }
        
        return upper;
    }
}
