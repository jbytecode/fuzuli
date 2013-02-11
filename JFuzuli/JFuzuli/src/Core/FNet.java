/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2013 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

package Core;

import Interpreter.Environment;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.Socket;
import java.net.URL;
import java.net.UnknownHostException;

public class FNet {
    
    public static Socket fsockopen (String host, Double port, Environment env) throws 
            UnknownHostException, 
            IOException {
        Socket s = new Socket(host, port.intValue());
        return(s);
    }
    
    public static void fsockwrite (Socket socket, Object what, Environment env) throws 
            IOException{
        String s = String.valueOf(what);
        socket.getOutputStream().write(s.getBytes());
        socket.getOutputStream().flush();
    }
    
    public static Object fsockread (Socket socket, Double byteCount, Environment env) {
        byte[] b = new byte[byteCount.intValue()];
        int result ;
        try{
            result = socket.getInputStream().read(b);
            if(result == -1){
                return (-1.0);
            }else{
                return(new String(b));
            }
        }catch (Exception e){
            return(-1.0);
        }
        
    }
    
    public static void fsockclose (Socket socket, Environment env) throws IOException{
        socket.close();
    }
    
    
    public static void clearBytes(byte[] b){
        for (int i=0;i<b.length;i++){
            b[i]=0;
        }
    }
    
    public static Object httpdownload (String url, Environment env)  throws Exception {
        URL u = new URL(url);
        HttpURLConnection con = (HttpURLConnection)u.openConnection();
        InputStream is = con.getInputStream();
        byte[] bytes = new byte[1024];
        StringBuilder buf = new StringBuilder();
        while(true){
            int result = is.read(bytes);
            if(result == -1){
                break;
            }
            buf.append(new String(bytes));
            clearBytes(bytes);
        }
        return(buf.toString());
    }
}
