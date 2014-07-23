<%-- 
    Document   : index
    Created on : 19.Nis.2014, 11:48:40
    Author     : hako
--%>

<%@page import="org.expr.SampleLoader"%>
<%@page import="java.io.PipedWriter"%>
<%@page import="java.io.DataOutputStream"%>
<%@page import="java.io.OutputStream"%>
<%@page import="java.io.PrintStream"%>
<%@page import="org.expr.WebOutput"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="Interpreter.*"%>


<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Fuzuli for Java, Online Interpreter</title>

    <script type="text/javascript">

    </script>
</head>
<body>
    <form method="post">
        <table width="100%">
            <tr><td width="95%">
                    <select name="samplecode">
                        <option value="">Custom code</option>
                        <option value="sum">Summing up an array</option>
                        <option value="triangle">Triangle</option>
                        <option value="functions">Custom Functions</option>
                        <option value="factorial">Recursive Factorial</option>
                        <option value="fibonacci">Recursive Fibonacci</option>
                        <option value="pi">Calculating Pi</option>
                        <option value="secant">Secant Method</option>
                        <option value="ols">Ordinary Least Squares</option>
                        <option value="string">String Functions</option>
                        <option value="bigmemory">Memory Allocation</option>
                        <option value="bublesort">Buble Sort</option>
                        <option value="quicksort">Quick Sort</option>
                        <option value="random">Random Numbers</option>
                        <option value="stack">Stack</option>
                    </select>
                </td></tr>
            <tr><td colspan="2">
                    <textarea name="code" rows="15" style="font-family: monospace; font-size: 12px; width:100%;"><%
                        String code = request.getParameter("code");
                        String samplecode = request.getParameter("samplecode");

                        if (samplecode == null){
                            samplecode = "";
                        }
                        if (samplecode.equals("")) {
                            if (code != null) {
                                out.print(code.trim());
                            } else {
                                out.println("(print \"Hello world!<br>\")");
                            }
                        } else {
                            out.println(SampleLoader.loadSample(samplecode + ".fzl"));
                        }
                        %></textarea>  
                </td>
            </tr>
            <tr>
                <td align="left"><input type="submit" value="Load or Run"></input>
            <td width="5%" align="right"><input type="reset" value="Clean"></input></td>
            </tr>
            <tr><td colspan="2">
            <div id="output" style="background-color: #000000; color: #ffffff; font-family: monospace; font-size: 12px;">
                <%
                    WebOutput wout = new WebOutput(null);
                    wout.setWriter(out);
                    System.setOut(wout);
                    System.setErr(wout);

                    if (code != null) {
                        Parser p = new Parser(code + "\n");
                        Environment globalEnv = new Environment(null);
                        p.resetParser();
                        while (true) {
                            Expression e = p.getNextExpression();
                            if (e == null) {
                                //out.println("Expression is null");
                                break;
                            }
                            try {
                                Object result = e.eval(globalEnv);
                                //out.println(result.toString()+"<br>");
                            } catch (RuntimeException rexp) {
                                out.println("<p style=\"color: red;\">" + rexp + "</p><br>");
                            }
                        }
                    }
                %>
            </div>
            </td></tr>

        </table>
    </form>
</body>
</html>