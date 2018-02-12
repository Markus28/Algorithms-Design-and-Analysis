package Utils;
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

public class PrimeList extends SortedArray<Integer>
{
    
    public PrimeList()
    {
        super(loadPrimes());
    }
    
    private int[] primeRankBounds(int k)  //According to Rossef, J. Barkley "Approximate formulas for some functions of prime numbers"
    {
        if(k <= 17)
        {
            return new int[] {0, 9};
        }
        
        double res = ((double)k)/Math.log(k);
        return new int[] {(int) res, ((int)(1.25506*res))+1};
    }
    
    public Integer primeCloseTo(Integer k)
    {
        int[] bounds = primeRankBounds(k);
        return get(approximateSearchBasic(k, bounds[0] - 1, bounds[1]+1));
    }
    
    public boolean isPrime(Integer k)
    {
        int[] bounds = primeRankBounds(k);
        return get(approximateSearchBasic(k, bounds[0]-1, bounds[1]+1)) == k;
    }
    
    private static Integer[] loadPrimes()
    {
        Integer[] primes = new Integer[1000000];
        File file = new File("primes1.txt");
        BufferedReader reader = null;
        try{
            reader = new BufferedReader(new FileReader(file));
            String text = null;
            int index = 0;
            int previous = 0;
            
            while ((text = reader.readLine()) != null) {
                for(String item: text.trim().split("\\s+"))
                {
                    if(item.length() != 0)
                    {
                        primes[index] = Integer.valueOf(item);
                        index++;
                    }
                }
            }    
        }
        
        catch(FileNotFoundException e){
            e.printStackTrace();
        }
        
        catch(IOException e)
        {
            e.printStackTrace();
        }
        
        finally{
            try{
                if (reader != null) 
                {
                    reader.close();
                }
            }
            
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }
        
        return primes;
    }
}

