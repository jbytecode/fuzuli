

package org.expr;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;


public class SampleLoader {
    
    public static String loadSample(String filename) throws Exception{
        InputStream is;
        is = SampleLoader.class.getResourceAsStream("/org/expr/samples/"+filename);
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder b = new StringBuilder();
        while(true){
            String line = reader.readLine();
            if (line == null){
                break;
            }
            b.append(line);
            b.append("\n");
        }
        reader.close();
        return(b.toString());
    }
}
